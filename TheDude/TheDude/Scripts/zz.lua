--Auto generated code based on map

local Entities = {}

local function _initEntities()
	local Entity_Scripted = Character.Create()
	Entity_Scripted:AddScript("Scripts/Player/PlayerModule.Lua")
	Entity_Scripted:setPosition(128,128)
	Entity_Scripted:setSize(32,32)
	table.insert(Entities, Entity_Scripted)
	local Entity_Scripted = Character.Create()
	Entity_Scripted:AddScript("Scripts/DVD.Lua")
	Entity_Scripted:setPosition(0,288)
	Entity_Scripted:setSize(32,32)
	table.insert(Entities, Entity_Scripted)
	local Entity_Scripted = Character.Create()
	Entity_Scripted:AddScript("Scripts/DVD.Lua")
	Entity_Scripted:setPosition(288,288)
	Entity_Scripted:setSize(32,32)
	table.insert(Entities, Entity_Scripted)
	local Entity_Scripted = Character.Create()
	Entity_Scripted:AddScript("Scripts/DVD.Lua")
	Entity_Scripted:setPosition(288,0)
	Entity_Scripted:setSize(32,32)
	table.insert(Entities, Entity_Scripted)
	local Entity_Scripted = Character.Create()
	Entity_Scripted:AddScript("Scripts/DVD.Lua")
	Entity_Scripted:setPosition(0,0)
	Entity_Scripted:setSize(32,32)
	table.insert(Entities, Entity_Scripted)

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
		_updateEntities()
		_collisionHandling()
	else
		setGameStatus(2)
	end
end

function draw()
	_drawEntities()
end
