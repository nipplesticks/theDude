function init()
	setColor(255, 0, 255)
	setPosition(50, 50)

	s1x = -1
	s1y = -1
end

function update()
	x1, y1 = getPosition()
	--print(x1)
	
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

function draw()

end