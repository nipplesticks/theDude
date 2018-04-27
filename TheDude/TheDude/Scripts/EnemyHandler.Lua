function init()
	e1 = Enemy.Create()
	e1:setPosition(500, 500)
	e1:setColor(60, 48, 255)
	e2 = Enemy.Create()
	e2:setPosition(0, 0)
	e2:setColor(77, 45, 136)
end

local s1x = 1
local s1y = 1
local s2x = 1
local s2y = 1

local function moveEmy1()
	x1, y1 = e1:getPosition()
	if (x1 + 100) > 1280 then
	s1x = s1x * (-1)
	elseif x1 < 0 then
	s1x = s1x * (-1)
	end
	if (y1 + 100) > 720 then
	s1y = s1y * (-1)
	elseif (y1 < 0) then
	s1y = s1y * (-1)
	end
	e1:move(s1x, s1y)
end

local function moveEmy2()
	x2, y2 = e2:getPosition()
	if (x2 + 100) > 1280 then
	s2x = s2x * (-1)
	elseif x2 < 0 then
	s2x = s2x * (-1)
	end
	if (y2 + 100) > 720 then
	s2y = s2y * (-1)
	elseif y2 < 0 then
	s2y = s2y * (-1)
	end
	e2:move(s2x, s2y)
end


function update()
	moveEmy1()
	moveEmy2()
	--print(player)
	--print(e2)

	if (isCollision(e2, e1)) then
		print("collision with e1")
	end
--	if (isCollision(pl, e2)) then
--		print("collision with e2")
--	end

end

function draw()
	e1:draw()
	e2:draw()
end