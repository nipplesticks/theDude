function init()
	Speed = 2.5
	setHPBar(-1,-1,-1,-1)
	setHealth(100)
	setAttack(0)
	setSprite("mario.jpg")
	wasPressed = false

	pistol = Weapon:Create("Scripts/mariosass.lua");
	ApplyWeapon(pistol)
end
local canJump = true
local lastY = 256
local JUMP_POWER = 0
local GRAVITY = 0.5
local lol1 = false
function update()
	
	local tempSpeed = Speed
	xPos, yPos = getPosition()

	if yPos == lastY then
		canJump = true
		if JUMP_POWER > 0 then
			JUMP_POWER = 0
		end	
	else 
		canJump = false
		pistol:Shoot(xPos,yPos +32 , 0,1)
		lastY = yPos
	end

	JUMP_POWER = GRAVITY + JUMP_POWER
	
	MoveRequest(0,JUMP_POWER)
	local lol2 = isKeyPressed("UP")

	if lol2 and not lol1 and canJump then
		JUMP_POWER = -10
	end
	lol1 = lol2
	if isKeyPressed("RIGHT") then
		MoveRequest(tempSpeed,0)
	elseif isKeyPressed("LEFT") then
		MoveRequest(-tempSpeed,0)
	end
end