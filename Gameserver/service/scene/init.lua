local skynet=require"skynet"
local s=require"service"
local marios={}  --[playerid]=mario
local actions={} --[playerid]=action
local keyframe=nil
local frame=nil

function table_leng(t)
	local leng=0
	for k, v in pairs(t) do
		if (v~=nil) then
			leng=leng+1
		end
	end
	return leng;
end

--由于游戏为24FPS，每四帧为一个关键帧，所以关键帧id为0，1，2，3，4，5
--该关键帧当前玩家操作
function action()
	local m={
		playerid=nil,
		keyframe=nil,
		action=nil,
	}
	return m
end

LEVEL={
	NORMAL=2,
	HUGE=3,
}

--角色类
function mario()
	local m={
		playerid=nil,
		node=nil,
		agent=nil,
		size=LEVEL.NORMAL,
		x=10,
		y=100,
	}
	return m
end

--当前游戏内所有玩家列表
local function mariolist_msg()
	local msg={"mariolist"}
	for i,v in pairs(mairos) do
		table.insert(msg,v.playerid)
		table.insert(msg,v.x)
		table.insert(msg,v.y)
		table.insert(msg,v.life)
		table.insert(msg,v.level)
	end
	return msg
end

--[[
--食物列表
local function mushroomlist_msg()
	local msg={"foodlist"}
	for i,v in pairs(mushrooms) do
		table.insert(msg,v.id)
		table.insert(msg,v.x)
		table.insert(msg,v.y)
	end
	return msg
end
]]
--广播信息
function broadcast(msg)
	for i,v in pairs(marios) do
		s.send(v.node,v.agent,"send",msg)
	end
end

function broadframes(msg)
	local playerid=tostring(msg[2])
	for i,v in pairs(marios) do
		if (playerid~=v.playerid) then
			s.send(v.node,v.agent,"send",msg)
		end
	end
end

function update_keyframe()
	--skynet.error("当前场景共有"..table_leng(marios).."个玩家")
	--skynet.error("当前场景共有"..table_leng(actions).."个玩家的关键帧")
	--只有一人独在场景不需要进行线上服务
	--[[if (table_leng(marios)<=1) then
		
		actions=nil
		keyframe=(keyframe+1)%4
		return true
	end]]
	local loop=0
	while true do
	--	skynet.error(keyframe)
		if(table_leng(marios)==0) then
			keyframe=(keyframe+1)%6
			break
		end
	--	skynet.error(keyframe)
		local onlineplayers=tonumber(table_leng(marios))
		local currentframes=tonumber(table_leng(actions))
		--skynet.error(onlineplayers.."------"..currentframes)
		if(onlineplayers==currentframes) then
			keyframe=(keyframe+1)%6
			for i,v in pairs(actions) do
				--[[
				local playerid=v.playerid
				local keyframe=v.keyframe
				local action=v.action
				]]
				local msg={"update",v.playerid,v.action}
				broadframes(msg)
				actions[v.playerid]=nil
			
			end
			local nxtmsg={"nextframe",keyframe}
			broadcast(nxtmsg)
			break
		else
			loop=loop+1
			skynet.sleep(10)
		end
		if(loop>=100) then
			local errmsg={"overtime"}
			--broadcast(errmsg)
		end
	end
end
function update()
	--每隔四帧为一帧关键帧
	if(frame%4==0) then
		update_keyframe()
	end
	return true
end

--客户端请求进入场景
s.resp.enter=function(source,playerid,node,agent)
	if marios[playerid] then
		return false
	end
	local b=mario()
	b.playerid=playerid
	b.node=node
	b.agent=agent

	--broadcast
	local entermsg={"newplayer",playerid}
	broadcast(entermsg)

	--record
	marios[playerid]=b
	--count nextbroadcast keyframe
	--[[local nextframe=nil
	if(frame%4==0)then
		nextframe=frame//4
	else
		nextframe=frame//4+1
	end
	nextframe=nextframe%6]]
	--response
	local ret_msg={"enter",0,keyframe}
	s.send(b.node,b.agent,"send",ret_msg)
	return true
end

s.resp.leave=function(source,playerid)
	if not marios[playerid] then
		return  false
	end

	marios[playerid]=nil
	
	local leavemsg={"leave",playerid}
	broadcast(leavemsg)
end

s.resp.stand=function(source,c_keyframe,playerid)
	--[[if actions[playerid]  then
		return
	end]]
	if (c_keyframe~=keyframe) then
		return false
	end
	local b=action()
	b.keyframe=c_keyframe
	b.playerid=playerid
	b.action="stand"
	actions[playerid]=b
	return true
end

s.resp.win=function(source,playerid)
	if not marios[playerid] then
		return false
	end
	marios[playerid]=nil

	--广播信息
	local winmsg={"win",playerid}
	broadcast(winmsg)

	--场景清空
	for i,v in pairs(marios) do
		s.send(v.node,v.agent,"win")
	end

	--清空当前场景所有玩家
	for i,v in pairs(marios) do
		marios[v.playerid]=nil
	end
	return true
end

s.resp.move=function(source,c_keyframe,playerid,dir)

	--当前关键帧已经收到
	--[[if  actions[playerid] then
		return
	end]]
	if(c_keyframe~=keyframe) then
		return false
	end

	local b=action()
	b.keyframe=c_keyframe
	b.playerid=playerid
	b.action="move,"..dir
	actions[playerid]=b
	return true
end

s.resp.jump=function(source,c_keyframe,playerid)
	--[[if actions[playerid] then
		return 
	end]]
	--check pipeiyufou
	if(c_keyframe~=keyframe) then
		return false
	end
	local b=action()
	b.keyframe=c_keyframe
	b.playerid=playerid
	b.action="jump"
	actions[playerid]=b
	return true
end

s.init=function()
	skynet.fork(function()
		--local stime=skynet.now()
		frame=1
		keyframe=0
		while true do
			pcall(update)
			--[[if not isok then
				skynet.error("something is not right")
			end]]
			frame=(frame+1)%24
			--skynet.error(frame)
			skynet.sleep(4)
		end
	end)
end

s.start(...)

