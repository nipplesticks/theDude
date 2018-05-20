function init()
	setHPBar(-1,-1,-1,-1)
	setHealth(100)
	setSprite("fiendeLol.png")
	setAttack(150);

	Speed = 2
end

local GRAVITY = 3
local lastxCoord = 256
local dir = -1
function update()
	x, y = getPosition()

	if x == lastxCoord then
		dir = dir * -1
	else
		lastxCoord = x
	end
	
	MoveRequest(dir, GRAVITY)
end