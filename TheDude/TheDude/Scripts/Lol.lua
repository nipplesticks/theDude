--Auto generated code based on map

local Entities = {}

local GoalTiles = {}
local function _initEntities()
	local Entity_Scripted = Character.Create()
	Entity_Scripted:AddScript("Scripts/Player/mario.lua")
	Entity_Scripted:setPosition(96,32)
	Entity_Scripted:setSize(32,32)
	table.insert(Entities, Entity_Scripted)
	local Entity_Scripted = Character.Create()
	Entity_Scripted:AddScript("Scripts/fiendeLol.lua")
	Entity_Scripted:setPosition(800,160)
	Entity_Scripted:setSize(32,32)
	table.insert(Entities, Entity_Scripted)
	local Entity_Scripted = Character.Create()
	Entity_Scripted:AddScript("Scripts/fiendeLol.lua")
	Entity_Scripted:setPosition(672,256)
	Entity_Scripted:setSize(32,32)
	table.insert(Entities, Entity_Scripted)
	local Entity_Scripted = Character.Create()
	Entity_Scripted:AddScript("Scripts/fiendeLol.lua")
	Entity_Scripted:setPosition(416,64)
	Entity_Scripted:setSize(32,32)
	table.insert(Entities, Entity_Scripted)
	local Entity_Scripted = Character.Create()
	Entity_Scripted:AddScript("Scripts/Goomba.lua")
	Entity_Scripted:setPosition(224,416)
	Entity_Scripted:setSize(32,32)
	table.insert(Entities, Entity_Scripted)
	local Entity_Scripted = Character.Create()
	Entity_Scripted:AddScript("Scripts/Goomba.lua")
	Entity_Scripted:setPosition(768,416)
	Entity_Scripted:setSize(32,32)
	table.insert(Entities, Entity_Scripted)
	local Entity_Scripted = Character.Create()
	Entity_Scripted:AddScript("Scripts/Goomba.lua")
	Entity_Scripted:setPosition(736,416)
	Entity_Scripted:setSize(32,32)
	table.insert(Entities, Entity_Scripted)
	local Entity_Scripted = Character.Create()
	Entity_Scripted:AddScript("Scripts/Goomba.lua")
	Entity_Scripted:setPosition(384,576)
	Entity_Scripted:setSize(32,32)
	table.insert(Entities, Entity_Scripted)
	local Entity_Scripted = Character.Create()
	Entity_Scripted:AddScript("Scripts/Goomba.lua")
	Entity_Scripted:setPosition(704,608)
	Entity_Scripted:setSize(32,32)
	table.insert(Entities, Entity_Scripted)
	local Entity_Scripted = Character.Create()
	Entity_Scripted:AddScript("Scripts/spike.lua")
	Entity_Scripted:setPosition(256,416)
	Entity_Scripted:setSize(32,32)
	table.insert(Entities, Entity_Scripted)
	local Entity_Scripted = Character.Create()
	Entity_Scripted:AddScript("Scripts/spike.lua")
	Entity_Scripted:setPosition(800,896)
	Entity_Scripted:setSize(32,32)
	table.insert(Entities, Entity_Scripted)
	local Entity_Scripted = Character.Create()
	Entity_Scripted:AddScript("Scripts/spike.lua")
	Entity_Scripted:setPosition(896,896)
	Entity_Scripted:setSize(32,32)
	table.insert(Entities, Entity_Scripted)
	local Entity_Scripted = Character.Create()
	Entity_Scripted:AddScript("Scripts/spike.lua")
	Entity_Scripted:setPosition(512,832)
	Entity_Scripted:setSize(32,32)
	table.insert(Entities, Entity_Scripted)

	local Goal = Character.Create()
	Goal:setPosition(832,896)
	Goal:setSize(32,32)
	table.insert(GoalTiles, Goal)
	local Goal = Character.Create()
	Goal:setPosition(864,896)
	Goal:setSize(32,32)
	table.insert(GoalTiles, Goal)
	SomeOneDied = false
end

local function _clean()										 
	for i = 2, #Entities, 1 do								 
		if Entities[i] ~= nil and Entities[i]:isDead() then	 
			table.remove(Entities, i)						 
		end												 
	end												 
end												 
local function _updateEntities()
	setPlayerPosition(Entities[1]:getPosition())
	for i = 1, #Entities, 1 do
		Entities[i]:Update()
		mRx, mRy = Entities[i]:getMoveRequest()
		if mRx ~= 0.0 or mRy ~= 0.0 then
			mx, my = canMove(Entities[i], mRx, mRy)
			if mx == 1 then
				mRx = 0.0 
			elseif mx == 2 then
				Entities[i]:AlterHealth(-100) -- Instant Death
			end
			if my == 1 then
				mRy = 0.0
			elseif my == 2 then
				Entities[i]:AlterHealth(-100) -- Instant Death
			end
			Entities[i]:Move(mRx, mRy)
			if Entities[i]:isDead() then
				SomeOneDied = true
			end
		end
	end
end

local function _drawEntities()
	for i = 1, #Entities, 1 do
		Entities[i]:Draw()
	end
end

local function _collisionHandling()
local bullets = Entities[1]:getProjectiles()									  
	for k = 1, #bullets, 1 do													  
		for j = 2, #Entities, 1 do												  
			if CheckCollision(Entities[j], bullets[k]) then						  
				Entities[j]:AlterHealth(-bullets[k]:getDamage())				  
				bullets[k] : Disable()											  
				end																  
				end																  
				end																  
																				  
				for i = 2, #Entities, 1 do										  
					isCollision = CheckCollision(Entities[1], Entities[i])		  
					if isCollision then											  
						Entities[1]:AlterHealth(Entities[i]:getAttack() * -1)	  
						Entities[i]:AlterHealth(Entities[1]:getAttack() * -1)	  
						end														  
						bullets = Entities[i] : getProjectiles()				  
						for k = 1, #bullets, 1 do								  
							if CheckCollision(Entities[1], bullets[k]) then		  
								Entities[1]:AlterHealth(-bullets[k]:getDamage())  
								bullets[k] : Disable()							  
								end												  
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
		for i = 1, #GoalTiles, 1 do
			if CheckCollision(Entities[1], GoalTiles[i]) then
				setGameStatus(1)
			end
		end
	else
		setGameStatus(2)
	end
if SomeOneDied then	
	_clean()		
	end				
end

function draw()
	_drawEntities()
end
