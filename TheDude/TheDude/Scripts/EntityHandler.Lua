-- Vars
local theDude
local playerSpeed
local enemy
local s1x
local s1y

-- Local Functions
local function _initPlayer()
	theDude = Character.Create()
	theDude:setPosition(500, 500)
	theDude:setColor(0, 255 ,0)
	playerSpeed = 2.5

end

local function _initEnemies()
	--Should be put inside table
	enemy = Character.Create()
	enemy:setColor(255, 0, 0)
	enemy:setPosition(100, 100)
	s1x = 1
	s1y = 1
end

local function _updatePlayer()
	local tempSpeed = playerSpeed
	if isKeyPressed("LSHIFT") then
		tempSpeed = tempSpeed * 1.5
	end

	if isKeyPressed("UP") then
		theDude:Move(0,-tempSpeed)
	elseif isKeyPressed("DOWN") then
		theDude:Move(0,tempSpeed)
	end

	if isKeyPressed("RIGHT") then
		theDude:Move(tempSpeed,0)
	elseif isKeyPressed("LEFT") then
		theDude:Move(-tempSpeed,0)
	end
end

local function _updateEnemies()
	x1, y1 = enemy:getPosition()
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
	enemy:Move(s1x, s1y)

end

local function _drawEnemies()
	enemy:Draw()

end

local function _collisionHandling()

	isCollision = CheckCollision(theDude, enemy)

	if isCollision then
		print("Enemy hit player")
	end

end

-- Functions to be called by Engine
function init()
	_initPlayer()
	_initEnemies()
end


function update()
	
	if isKeyPressed("ESC") then
		ExitGame()
	else
		_updatePlayer()
		_updateEnemies()
		_collisionHandling()
	end

end

function draw()
	theDude:Draw()
	_drawEnemies()
end

