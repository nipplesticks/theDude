function init()
	setSize(6,6)
	setDamage(12)
	setColor(0, 0, 0)
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