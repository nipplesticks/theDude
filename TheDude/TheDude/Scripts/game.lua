--Auto generated code based on map

local Entities = {}
local ENTITYS_AMOUNT = 2

local function _initEntities()
	local Entity_Scripted = Character.Create()
	Entity_Scripted:AddScript("Scripts/PlayerModule.Lua")
	Entity_Scripted:setPosition(0,0)
	Entity_Scripted:setSize(32,32)
	table.insert(Entities, Entity_Scripted)
	local Entity_Scripted = Character.Create()
	Entity_Scripted:AddScript("Scripts/DVD.Lua")
	Entity_Scripted:setPosition(128,128)
	Entity_Scripted:setSize(32,32)
	table.insert(Entities, Entity_Scripted)
end

local function _updateEntities()
	setPlayerPosition(Entities[1]:getPosition())
	for i = 1, #Entities, 1 do
		Entities[i]:Update()
	end
end

local function _drawEntities()
	for i = 1, #Entities, 1 do
		Entities[i]:Draw()
	end
end

local function _collisionHandling()
	for i = 2, #Entities, 1 do
		isCollision = CheckCollision(Entities[1], Entities[i])		if isCollision then
			Entities[1]:AlterHealth(Entities[i]:getAttack() * -1)
		end
	end
end

function init()
	_initEntities()
end

function update()
	if isKeyPressed("ESC") then
		ExitGame()
	elseif Entities[1]:isDead() == false then
		Entities[1]:Update()
		_updateEntities()
		_collisionHandling()
	end
end

function draw()
	_drawEntities()
end