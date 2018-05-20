--Auto generated code based on map

local Entities = {}

local GoalTiles = {}
local function _initEntities()
	local Entity_Scripted = Character.Create()
	Entity_Scripted:AddScript("Scripts/Player/mario.lua")
	Entity_Scripted:setPosition(160,576)
	Entity_Scripted:setSize(32,32)
	table.insert(Entities, Entity_Scripted)
	local Entity_Scripted = Character.Create()
	Entity_Scripted:AddScript("Scripts/Goomba.lua")
	Entity_Scripted:setPosition(736,576)
	Entity_Scripted:setSize(32,32)
	table.insert(Entities, Entity_Scripted)
	local Entity_Scripted = Character.Create()
	Entity_Scripted:AddScript("Scripts/Goomba.lua")
	Entity_Scripted:setPosition(960,576)
	Entity_Scripted:setSize(32,32)
	table.insert(Entities, Entity_Scripted)

	local Goal = Character.Create()
	Goal:setPosition(1312,544)
	Goal:setSize(32,32)
	table.insert(GoalTiles, Goal)
	local Goal = Character.Create()
	Goal:setPosition(1312,576)
	Goal:setSize(32,32)
	table.insert(GoalTiles, Goal)
	local Goal = Character.Create()
	Goal:setPosition(1344,544)
	Goal:setSize(32,32)
	table.insert(GoalTiles, Goal)
	local Goal = Character.Create()
	Goal:setPosition(1344,576)
	Goal:setSize(32,32)
	table.insert(GoalTiles, Goal)
end

local function _updateEntities()
	setPlayerPosition(Entities[1]:getPosition())
	for i = 1, #Entities, 1 do
		Entities[i]:Update()
		mRx, mRy = Entities[i]:getMoveRequest()
		if mRx ~= 0.0 or mRy ~= 0.0 then
			mx, my = canMove(Entities[i], mRx, mRy)
			if mx == false then
				 mRx = 0.0 
			end
			if my == false then
				 mRy = 0.0
			end
			Entities[i]:Move(mRx, mRy)
		end
	end
end

local function _drawEntities()
	for i = 1, #Entities, 1 do
		Entities[i]:Draw()
	end
end

local function _collisionHandling()
	for i = 2, #Entities, 1 do
		isCollision = CheckCollision(Entities[1], Entities[i])
		if isCollision then
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
		for i = 1, #GoalTiles, 1 do
			if CheckCollision(Entities[1], GoalTiles[i]) then
				setGameStatus(1)
			end
		end
		_updateEntities()
		_collisionHandling()
	else
		setGameStatus(2)
	end
end

function draw()
	_drawEntities()
end
