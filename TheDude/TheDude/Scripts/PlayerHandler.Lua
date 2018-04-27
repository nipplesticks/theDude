local playerHandler = {}

local speed = 2.5

function init()
	player = Player.Create()
	player:setPosition(500, 500)
end

function update()
	if isKeyPressed("W") then
	player:move(0,-speed)
	player:setColor(0, 255, 0)
	elseif isKeyPressed("S") then
	player:move(0,speed)
	player:setColor(255, 0, 255)
	end
	if isKeyPressed("D") then
	player:move(speed,0)
	player:setColor(255, 0, 0)
	elseif isKeyPressed("A") then
	player:move(-speed,0)
	player:setColor(0, 0, 255)
	end
	
end

function playerHandler.getPlayer()
	local p = player
	return p
end

function draw()
	player:draw()
end

return playerHandler