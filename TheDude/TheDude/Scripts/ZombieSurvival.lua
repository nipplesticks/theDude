--Auto generated code based on map

local Entities = {}

local function _initEntities()
	local Entity_Scripted = Character.Create()
	Entity_Scripted:AddScript("Scripts/Player/RunAndGunner.lua")
	Entity_Scripted:setPosition(192,32)
	Entity_Scripted:setSize(32,32)
	table.insert(Entities, Entity_Scripted)
	local Entity_Scripted = Character.Create()
	Entity_Scripted:AddScript("Scripts/ZombieNormal.lua")
	Entity_Scripted:setPosition(352,1440)
	Entity_Scripted:setSize(32,32)
	table.insert(Entities, Entity_Scripted)
	local Entity_Scripted = Character.Create()
	Entity_Scripted:AddScript("Scripts/ZombieNormal.lua")
	Entity_Scripted:setPosition(800,1216)
	Entity_Scripted:setSize(32,32)
	table.insert(Entities, Entity_Scripted)
	local Entity_Scripted = Character.Create()
	Entity_Scripted:AddScript("Scripts/ZombieNormal.lua")
	Entity_Scripted:setPosition(1056,704)
	Entity_Scripted:setSize(32,32)
	table.insert(Entities, Entity_Scripted)
	local Entity_Scripted = Character.Create()
	Entity_Scripted:AddScript("Scripts/ZombieNormal.lua")
	Entity_Scripted:setPosition(1344,480)
	Entity_Scripted:setSize(32,32)
	table.insert(Entities, Entity_Scripted)
	local Entity_Scripted = Character.Create()
	Entity_Scripted:AddScript("Scripts/ZombieNormal.lua")
	Entity_Scripted:setPosition(384,768)
	Entity_Scripted:setSize(32,32)
	table.insert(Entities, Entity_Scripted)
	local Entity_Scripted = Character.Create()
	Entity_Scripted:AddScript("Scripts/ZombieRange.lua")
	Entity_Scripted:setPosition(608,992)
	Entity_Scripted:setSize(32,32)
	table.insert(Entities, Entity_Scripted)
	local Entity_Scripted = Character.Create()
	Entity_Scripted:AddScript("Scripts/ZombieRange.lua")
	Entity_Scripted:setPosition(1120,1056)
	Entity_Scripted:setSize(32,32)
	table.insert(Entities, Entity_Scripted)
	local Entity_Scripted = Character.Create()
	Entity_Scripted:AddScript("Scripts/ZombieRange.lua")
	Entity_Scripted:setPosition(1440,1472)
	Entity_Scripted:setSize(32,32)
	table.insert(Entities, Entity_Scripted)
	local Entity_Scripted = Character.Create()
	Entity_Scripted:AddScript("Scripts/ZombieRange.lua")
	Entity_Scripted:setPosition(928,320)
	Entity_Scripted:setSize(32,32)
	table.insert(Entities, Entity_Scripted)
	local Entity_Scripted = Character.Create()
	Entity_Scripted:AddScript("Scripts/ZombieRange.lua")
	Entity_Scripted:setPosition(192,608)
	Entity_Scripted:setSize(32,32)
	table.insert(Entities, Entity_Scripted)

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
		if #Entities == 1 then
			setGameStatus(1)
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
