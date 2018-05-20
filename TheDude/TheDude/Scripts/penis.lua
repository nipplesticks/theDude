function init()
	setSize(32,32)
	setDamage(5)
	
	dirX, dirY = getDirection()
	Live = 0

end

function update()
	Move(dirX * 10, dirY * 10)
	Live = Live + (1 / 60)

	if Live > 2 then
		Disable()
	end

end