
function init()
	e1 = Enemy.Create()
	e1:setPosition(500, 500)
	e1:setColor(60, 48, 255)
	e2 = Enemy.Create()
	e2:setPosition(250, 250)
	e2:setColor(77, 45, 136)

end

function update()
	
end

function draw()
	e1:draw()
	e2:draw()
end