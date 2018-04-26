
function init()
	P = Player.Create()
	P:setPosition(500, 500)

	P2 = Player.Create()
	P2:setPosition(0,0)

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

	if isKeyPressed("I") then
	P2:move(0,-speed)
	P2:setColor(0, 255, 0)
	elseif isKeyPressed("K") then
	P2:move(0,speed)
	P2:setColor(255, 0, 255)
	end
	if isKeyPressed("L") then
	P2:move(speed,0)
	P2:setColor(255, 0, 0)
	elseif isKeyPressed("J") then
	P2:move(-speed,0)
	P2:setColor(0, 0, 255)
	end



end

function draw()
	P:draw()
	P2:draw()
end