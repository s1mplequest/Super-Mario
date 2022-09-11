local skynet=require "skynet"
local s =require"service"
local socket=require"skynet.socket"
local runconfig=require"runconfig"

conns ={} --[socket_id]=conn
players={} --[playerid]=gateplayer

--连接类
function conn()
	local m ={
		--connect_flag
		fd=nil,
		playerid=nil,
	}

	return m
end

--玩家类
function gateplayer()
	local m ={
		playerid=nil,
		agent=nil,
		conn=nil,
	}
	return m
end

--用于消息拆包
local str_unpack =function(msgstr)
	local msg= {}
	while true do
		local arg,rest=string.match(msgstr,"(.-),(.*)")
		if arg then
			msgstr =rest
			table.insert(msg,arg)
		else
			table.insert(msg,msgstr)
			break
		end
	end
	return msg[1],msg
end

--用于消息组包
local str_pack =function(cmd,msg)
	return table.concat(msg,",").."\r\n"
end

--消息经过出来返回给客户端
s.resp.send_by_fd=function(source,fd,msg)
	if not conns[fd] then
		skynet.error("not a conns..")
		return 
	end
	
	local buff=str_pack(msg[1],msg)
	skynet.error("send "..fd.."["..msg[1].."]{"..table.concat(msg,",").."}")
		socket.write(fd,buff)
end

--agent消息转发给gateway并由getaway转给回客户端
s.resp.send=function(source,playerid,msg)
	local gplayer=players[playerid]
	if gplayer==nil then
		skynet.error("not a pkayerid....")
		return
	end
	local c=gplayer.conn
	if c==nil then
		skynet.error("not a conn in gateplayer class")
		return
	end

	s.resp.send_by_fd(nil,c.fd,msg)
end

--通知网关连接成功，进行客户端与agent（玩家类）的连接
s.resp.sure_agent=function(source,fd,playerid,agent)
	local conn=conns[fd]
	if not conn then
		skynet.call("agentmgr","lua","reqkick",playerid,"未完成登录即下线")
		return false
	end

	conn.playerid=playerid

	local gplayer=gateplayer()
	gplayer.playerid=playerid
	gplayer.agent=agent
	gplayer.conn=conn
	players[playerid]=gplayer

	return true
end

--客户端情况，进行断连
local disconnect= function(fd)
	local c= conns[fd]
	if not c then
		return
	end

	local playerid=c.playerid

	--还没有完成登录
	if not playerid then
		return
	--已在游戏中
	else
		players[playerid]=nil
		local reason ="断线"
		skynet.call("agentmgr","lua","reqkick",playerid,reason)
	end
end

--处理由agentmgr传来的踢下线操作
s.resp.kick=function(source,playerid)
	local gplayer=players[playerid]
	if not gplayer then
		return 
	end
	
	local c=gplayer.conn
		players[playerid]=nil
	
	if not c then
		return
	end

	conns[c.fd]=nil

	disconnect(c.fd)
	socket.close(c.fd)
end

s.resp.quit=function(source,playerid)
	local gplayer=players[playerid]
	local conn=gplayer.conn
	--players[playerid]=nil
	--conns[conn]=nil
	local reason="正常退出"
	skynet.call("agentmgr","lua","reqkick",playerid,reason)
end

--处理传递过来的信息,转发给相应的服务线程
local process_msg=function(fd,msgstr)
	local cmd,msg=str_unpack(msgstr)
	skynet.error("recv"..fd.."["..cmd.."]{"..table.concat(msg,",").."}")

	local conn=conns[fd]
	local playerid=conn.playerid
	if not playerid then
		local node=skynet.getenv("node")
		local nodecfg=runconfig[node]
		local loginid=math.random(1,#nodecfg.login)
		local login="login"..loginid
		
		skynet.send(login,"lua","client",fd,cmd,msg)
	
	else
		local gplayer=players[playerid]
		local agent=gplayer.agent
		
		skynet.send(agent,"lua","client",cmd,msg)
	
	end
end

--为发过来的信息流进行拆分成一个命令
local process_buff =function(fd,readbuff)
	while true do
		local msgstr,rest=string.match( readbuff, "(.-)\r\n(.*)")
		if msgstr then
			readbuff=rest
			process_msg(fd,msgstr)
		else
			return readbuff
		end
	end
end

--循环读取客户端发来的消息，若无则关闭连接，（维持连接）
local recv_loop=function(fd)
	socket.start(fd)
	skynet.error("socket connected"..fd)
	local readbuff =""
	while true do
		local recvstr=socket.read(fd)
		if recvstr then
			readbuff=readbuff..recvstr
			readbuff=process_buff(fd,readbuff)
		else
			skynet.error("socket close"..fd)
			disconnect(fd)
			socket.close(fd)
			return
		end
	end
end

--记录连接信息
local connect=function(fd,addr)
	print("connect from "..addr.." "..fd)
	local c= conn()
	conns[fd]=c
	c.fd=fd
	skynet.fork(recv_loop,fd)
end

--service初始化
function s.init()
	skynet.error("[Start]"..s.name.."  "..s.id )
	local node=skynet.getenv("node")
	local nodecfg=runconfig[node]
	local port=nodecfg.gateway[s.id].port

	local listenfd=socket.listen("0.0.0.0",port)
	skynet.error("Listen socket:","0.0.0.0",port)
	socket.start(listenfd,connect)
end

s.start(...)
