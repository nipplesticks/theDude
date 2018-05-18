function init()
	Speed = 2.5
	setHPBar(50,110,100,10)
	setHealth(100)
	setPosition(0, 0)
	setSprite("zelda.png")
	wasPressed = false

	pistol = Weapon:Create("Scripts/penis.lua");
	ApplyWeapon(pistol)
end

function update()

if wasPressed == false then
	if isKeyPressed("K") then
		pc, ps = getPosition();
		pistol:Shoot(pc, ps, 0, 0);
		wasPressed = true
	elseif isKeyPressed("L") then
		AlterHealth(5)
		wasPressed = true
	end
elseif wasPressed == true then
	if isKeyPressed("K") == false and isKeyPressed("L") == false then
		wasPressed = false;
	end
end
local tempSpeed = Speed
	if isKeyPressed("LSHIFT") then
		tempSpeed = tempSpeed * 2.0
	end

	if isKeyPressed("UP") then
		MoveRequest(0,-tempSpeed)
	elseif isKeyPressed("DOWN") then
		MoveRequest(0,tempSpeed)
	end

	if isKeyPressed("RIGHT") then
		MoveRequest(tempSpeed,0)
	elseif isKeyPressed("LEFT") then
		MoveRequest(-tempSpeed,0)
	end
end