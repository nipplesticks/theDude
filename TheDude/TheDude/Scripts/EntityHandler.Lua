-- Local Functions
local function _initPlayer()
	theDude = Character.Create()
	theDude:setPosition(500, 500)
	theDude:setColor(0, 255 ,0)
	playerSpeed = 2.5

end

local function _initEnemies()
	--Should be put inside table
	Enemy_Scripted = Character.Create()
	Enemy_Scripted:AddScript("Scripts/DVD.Lua")
end

local function _updatePlayer()
	local tempSpeed = playerSpeed
	if isKeyPressed("LSHIFT") then
		tempSpeed = tempSpeed * 3.0
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
	Enemy_Scripted:Update()

end

local function _drawEnemies()
	Enemy_Scripted:Draw()
end

local function _collisionHandling()

	isCollision = CheckCollision(theDude, Enemy_Scripted)

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

