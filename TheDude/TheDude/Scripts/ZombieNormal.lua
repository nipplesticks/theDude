function init()
	setHPBar(50,110,50,10)
	setHealth(100)
	setSprite("Zombie_Normal.png")
	setAttack(5);
	Counter = 0
	Speed = 2
	Range = 150
	Aggro = 1
	Direction = {}
	Direction.x = -1
	Direction.y = -1
end

update = 0
function update()
	if getDistanceToPlayer() < (Range * Aggro) then
		setColor(255, 200, 200)
		Aggro = 2
		local mPos = {}
		mPos.x, mPos.y = getPosition()
		local mSize = {}
		mSize.x, mSize.y = getSize()
		mPos.x = mPos.x + mSize.x * 0.5
		mPos.y = mPos.y + mSize.y * 0.5

		local pPos = {}
		pPos.x, pPos.y = getPlayerPosition()

		local direction = {}
		direction.x = pPos.x - mPos.x
		direction.y = pPos.y - mPos.y
		
		local length = math.sqrt(direction.x * direction.x + direction.y * direction.y)
		direction.x = (direction.x / length) * Speed
		direction.y = (direction.y / length) * Speed
		MoveRequest(direction.x, direction.y)
	else
	setColor(255, 255, 255)
		Aggro = 1
		Counter = Counter + 1
		x1, y1 = getPosition()
		math.randomseed(Counter + os.time() * x1 * y1)
		if Counter > 200 then
			Counter = 0
			Direction.x = math.random(-1, 1) * 0.5
			
			math.random(-1, 1)
			math.random(-1, 1)
			math.random(-1, 1)
			math.random(-1, 1)
			Direction.y = math.random(-1, 1) * 0.5
		end
		
		MoveRequest(Direction.x, Direction.y)
	end
end