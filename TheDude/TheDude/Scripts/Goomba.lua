function init()
	setHPBar(-1,-1,-1,-1)
	setHealth(100)
	setColor(255, 0, 255)
	setSprite("goomba.png")
	setAttack(100);
	s1x = -1
	s1y = -1

	Speed = 2
	Range = 300
	Aggro = 1
end

local lastxCoord = 256
local dir = -1
function update()
	x, y = getPosition()

	if x == lastxCoord then
		dir = dir * -1
	else
		lastxCoord = x
	end

	MoveRequest(dir,0)
end