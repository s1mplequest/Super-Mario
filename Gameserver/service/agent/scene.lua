local skynet=require"skynet"
local s= require"service"
local runconfig=require"runconfig"
local mynode=skynet.getenv("node")

s.snode=nil  --scene_node
s.sname=nil  --  __scene_id


local function random_scene()
	--选择node
	local nodes = {}
	for i, v in pairs(runconfig.scene) do
		table.insert(nodes, i)
		if runconfig.scene[mynode] then
	 		table.insert(nodes, mynode)
		end
	end
	local idx = math.random( 1, #nodes)
	local scenenode = nodes[idx]
	--具体场景
	local scenelist = runconfig.scene[scenenode]
	local idx = math.random( 1, #scenelist)
	local sceneid = scenelist[idx]
	return scenenode, sceneid
end

--加入场景
s.client.enter = function(msg)
	  if s.sname then
	    	return {"enter",1,"已在场景"}
	  end
	  local snode, sid = random_scene()
	  local sname = "scene"..sid
	  local isok = s.call(snode, sname, "enter", s.id, mynode, skynet.self())
	  if not isok then
	  	return {"enter",1,"进入失败"}
	  end
	  s.snode = snode
	  s.sname = sname
	  return nil
end

--离开场景
s.client.leave = function(msg)
	if not s.sname then
		return{"leave",0,"已经退出了，请不要重复退出"}
	end
	s.call(s.snode,s.sname,"leave",s.id)
	--[[if not isok then
		return {"leave","1","退出失败请重试"}
	end]]
	s.snode=nil
	s.sname=nil
	return {"leave","1","退出成功"}
end

s.client.win  = function(msg)
	local isok=s.call(s.snode,s.sname,"win",s.id)
	if not isok then 
		return{"win","0","网络延迟。。"}
	end
	s.snode=nil
	s.sname=nil
	return{"win","1"}
end

s.client.update=function(msg)
	local keyframe=tonumber(msg[2])
	local action=tostring(msg[3])
	
	if (action=="move") then
		local dir=tostring(msg[4])
		
		local isok=s.call(s.snode,s.sname,"move",keyframe,s.id,dir)
		if not isok then
			return {"dismatch","keyframe"}	
		end
	end
	if(action=="jump") then
		
		local isok=s.call(s.snode,s.sname,"jump",keyframe,s.id)
		if not isok then
			return {"dismatch","keyframe"}
		end
	end
	if(action=="stand")then
		local isok=s.call(s.snode,s.sname,"stand",keyframe,s.id)
		
		if not isok then
			return {"dismatch","keyframe"}
		end
	end
end

s.client.quit=function()
	skynet.error(s.gate)
	s.call(s.gate,"lua","quit",s.id)
end

s.resp.win=function()
	s.snode=nil
	s.sname=nil
end
s.leave_scene = function()
	--不在场景
	if not s.sname then
		return
	end
	s.call(s.snode, s.sname, "leave", s.id)
	s.snode = nil
	s.sname = nil
end
