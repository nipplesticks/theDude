local Enemies = {}
local ENEMY_AMOUNT = 5
local function _initPlayer()
	theDude = Character.Create()
	theDude:setPosition(500, 500)
	theDude:setColor(0, 255 ,0)
	theDude:setSprite("zelda.png")
	playerSpeed = 2.5
end

local function _initEnemies()
	--Should be put inside table
	for i = 1, ENEMY_AMOUNT, 1 do 
		local Enemy_Scripted = Character.Create()
		Enemy_Scripted:AddScript("Scripts/DVD.Lua")
		Enemy_Scripted:setPosition(i * 75, i * 75)
		table.insert(Enemies, Enemy_Scripted)
	end
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
	setPlayerPosition(theDude:getPosition())
end

local function _updateEnemies()
	for i = 1, #Enemies, 1 do
		Enemies[i]:Update()
	end
end

local function _drawEnemies()
	for i = 1, #Enemies, 1 do
		Enemies[i]:Draw()
	end
end

local function _collisionHandling()
	for i = 1, #Enemies, 1 do
		isCollision = CheckCollision(theDude, Enemies[i])

		if isCollision then
			--print("Enemy#" .. i .. " hit player")
		end
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