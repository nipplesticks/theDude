function init()
	setHPBar(-1,-1,-1,-1)
	setHealth(3000)
	setSprite("spike.png")
	setAttack(100);
	s1x = -1
	s1y = -1

	Speed = 2
	Range = 300
	Aggro = 1

end


local lastxCoord = 256
local dir = -1
local MAX_UP = 200
startY = -1.0
lastY = 256
getFirst = false

function update()
	currentX, currentY = getPosition()

	if getFirst == false then
		startY = currentY
		getFirst = true
	end

	deltaY = startY - currentY

	if deltaY > MAX_UP then
		dir = dir * -1
		Speed = 6
	elseif deltaY == lastY then
		dir = dir * -1
		speed = 3
	end
	lastY = deltaY

	

	
	MoveRequest(0, dir * Speed)
end