function init()
	setSize(6,6)
	setDamage(8)
	setColor(255, 255, 255)
	dirX, dirY = getDirection()
	Live = 0
	
	Speed = 10
	px, py = getPosition()
	NoiceX = 12
	NoiceY = 12
	math.randomseed(os.time() * px * py)
	math.random(); math.random(); math.random()
	NoiceX = math.random(-NoiceX, NoiceX) * 0.05
	NoiceY = math.random(-NoiceY, NoiceY) * 0.05
	
	local lol = math.random(-1, 1)
	dirX = dirX + (NoiceX * lol)
	dirY = dirY + (NoiceY * lol)
	
end

function update()
	Move(dirX * Speed, dirY * Speed)
	Live = Live + (1 / 60)



	if Live > 2 then
		Disable()
	end

end