local skynet=require"skynet"
local s=require"service"
local mysql=require"skynet.db.mysql"


s.client={}

--接受client类型消息，并在login里进行转发
s.resp.client=function(source,fd,cmd,msg)
	if s.client[cmd] then
		local ret_msg=s.client[cmd](fd,msg,source)
		skynet.send(source,"lua","send_by_fd",fd,ret_msg)
	else
		skynet.error('s.resp.client fail[loginserver]',cmd)
	end
end

--接受gateway发来的来自客户端的登录请求
s.client.login=function(fd,msg,source)
	local playerid=tostring(msg[2])
	local pw=tostring(msg[3])
	local gate=source
	node=skynet.getenv("node")
	local db=mysql.connect({
		host="127.0.0.1",
		port=3306,
		database="gameserver",
		user="gameuser",
		password="235712",
		max_packet_size=1024*1024,
		on_connect=nil
	})
	local res=db:query("select login(\'"..playerid.."\',\'"..pw.."\') as result")
	local result=tonumber(res[1].result)
	db:disconnect()


	if result == 0 then 
		return {"login",0,"用户名或密码不正确"}
	end


	local isok,agent=skynet.call("agentmgr","lua","reqlogin",playerid,node,gate)
	

	if not isok then
		return {"login",0,"请求mgr失败请稍后再试"}
	end

	local isok=skynet.call(gate,"lua","sure_agent",fd,playerid,agent)
	if not isok then
		return {"login",0,"gate注册失败"}
	end
	skynet.error(playerid.."logs in now...")

	return {"login",1,"登录成功"}
end

--接受来gateway发来的客户端注册请求
s.client.register=function(fd,msg,source)
	local playerid=tostring(msg[2])
	local password=tostring(msg[3])
	local db =mysql.connect({
		host="127.0.0.1",
		port=3306,
		database="gameserver",
		user="gameuser",
		password="235712",
		max_packet_size=1024*1024,
		on_connect=nil
	})
	local res=db:query("select register(\'"..playerid.."\',\'"..password.."\') as result")
	local result=tonumber(res[1].result)
	db:disconnect()
	if reslut ==0 then 
		return {"register",0,"已有同名用户"}
	else
		return {"register","1","注册成功"}
	end

end
s.start(...)
