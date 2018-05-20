function init()
	setSize(32,12)
	setColor(127,255,127)
	setDamage(100)
	
	dirX, dirY = getDirection()
	Live = 0

end

function update()
	Move(dirX * 10, dirY * 10)
	Live = Live + (1 / 60)

	if Live > 0 then
		Disable()
	end

end