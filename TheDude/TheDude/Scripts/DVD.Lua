require("Scripts.EntityHandler")

function init()
	setColor(255, 0, 255)
	setPosition(50, 50)
	setSprite("jew.jpg")
	s1x = -1
	s1y = -1

	Speed = 2
	Range = 300
	Aggro = 1
end

update = 0
function update()
	if getDistanceToPlayer() < (Range * Aggro) then
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
		Move(direction.x, direction.y)
	else
		Aggro = 1
		x1, y1 = getPosition()
		if (x1 + 100) > 1280 then
		s1x = s1x * (-1)
		elseif x1 < 0 then
		s1x = s1x * (-1)
		end
		if (y1 + 100) > 720 then
		s1y = s1y * (-1)
		elseif (y1 < 0) then
		s1y = s1y * (-1)
		end
		Move(s1x, s1y)
	end
end

draw = 0
function draw()

end