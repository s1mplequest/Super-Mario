local skynet=require"skynet"
local s=require"service"

s.client={}
s.gate=nil

require"scene"

--进行消息转发
s.resp.client=function(source,cmd,msg)
	s.gate=source
	if s.client[cmd] then
		local ret_msg=s.client[cmd](msg,source)
		if ret_msg then
			skynet.send(source,"lua","send",s.id,ret_msg)
		end
	else
		skynet.error("s.resp.client fail..",cmd)
	end
end

--保存并退出
s.resp.kick =function(source)
	s.leave_scene()
	skynet.sleep(200)
end

--退出登录
s.resp.exit=function(source)
	skynet.exit()
end

s.resp.send=function(source,msg)
	skynet.send(s.gate,"lua","send",s.id,msg)
end

s.init=function()
	skynet.sleep(200)
end

s.start(...)
