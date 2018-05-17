local Enemies = {}
local ENEMY_AMOUNT = 5

local function _initEntities()
	--Should be put inside table
	for i = 1, ENEMY_AMOUNT, 1 do 
		local Enemy_Scripted = Character.Create()
		Enemy_Scripted:AddScript("Scripts/DVD.Lua")
		Enemy_Scripted:setPosition(i * 100, i * 100)
		table.insert(Enemies, Enemy_Scripted)
	end
	theDude = Character.Create()
	theDude:AddScript("Scripts/PlayerModule.Lua")
end

local function _updateEnemies()
	setPlayerPosition(theDude:getPosition())
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
			--theDude:AlterHealth(-1)

		end
	end
end

-- Functions to be called by Engine
function init()
	_initEntities()
end


function update()
	if isKeyPressed("ESC") then
		ExitGame()
	elseif theDude:isDead() == false then
		theDude:Update()
		_updateEnemies()
		_collisionHandling()
	end
end

function draw()
	theDude:Draw()
	_drawEnemies()
end