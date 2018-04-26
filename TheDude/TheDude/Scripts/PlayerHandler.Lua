
function init()
	P = Player.Create()
	P:setPosition(500, 500)



end

speed = 2.5

function update()
	if isKeyPressed("W") then
	P:move(0,-speed)
	P:setColor(0, 255, 0)
	elseif isKeyPressed("S") then
	P:move(0,speed)
	P:setColor(255, 0, 255)
	end
	if isKeyPressed("D") then
	P:move(speed,0)
	P:setColor(255, 0, 0)
	elseif isKeyPressed("A") then
	P:move(-speed,0)
	P:setColor(0, 0, 255)
	end
end

function draw()
	P:draw()
end