	local Pistol = {}
	local AK = {}
	local ActiveGun = {}
	local Speed
	local canShoot
	local counter
function init()
	setHPBar(50,115,110,10)
	setHealth(100)
	setSprite("Corn.png")
	setAttack(0)

	Pistol.Gun = Weapon:Create("Scripts/Weapons/pistol.lua")
	Pistol.Ammo = 12
	Pistol.MaxAmmo = 12
	Pistol.ID = 1
	Pistol.Auto = false
	ApplyWeapon(Pistol.Gun)

	AK.Gun = Weapon:Create("Scripts/Weapons/AK.lua")
	AK.Ammo = 32
	AK.MaxAmmo = 32
	AK.ID = 2
	AK.Auto = true
	NotRPM = 7

	ApplyWeapon(AK.Gun)



	ActiveGun = Pistol
	Speed = 2.5
	canShoot = true
end


local function _movement()
	local tempSpeed = Speed
	if isKeyPressed("lshift") then
		tempSpeed = tempSpeed * 1.5
	end
	if isKeyPressed("W") then
		MoveRequest(0, -tempSpeed)	
	elseif isKeyPressed("S") then
		MoveRequest(0, tempSpeed)
	end

	if isKeyPressed("A") then
		MoveRequest(-tempSpeed, 0)	
	elseif isKeyPressed("D") then
		MoveRequest(tempSpeed, 0)
	end
end


local function _weaponLogic()
	if isKeyPressed("1") then
		--Swap to Pistol
		if ActiveGun.ID == AK.ID then
			AK = ActiveGun
			ActiveGun = Pistol
		end
	elseif isKeyPressed("2") then
		--Swap to AK
		if ActiveGun.ID == Pistol.ID then
			Pistol = ActiveGun
			ActiveGun = AK
		end
	end

	if ActiveGun.Auto == true then
		counter = counter + 1


		if counter > NotRPM then
			counter = 0
		end
			

	else
		counter = 0
	end

	if isKeyPressed("space") then
		ActiveGun.Ammo = ActiveGun.MaxAmmo
	end


	if counter == 0 then
		if ActiveGun.Ammo == 0 then
			canShoot = false
		end

		if isKeyPressed("lmouse") and canShoot == true then
			--shoot
			x, y = getPosition()
			sx, sy = getSize()
			mx, my = getMousePos()

			ActiveGun.Gun:Shoot(x + sx / 2, y + sy / 2, mx, my)
			ActiveGun.Ammo = ActiveGun.Ammo - 1

			if ActiveGun.Auto == false then
				canShoot = false
			end
		end
	end

	if isKeyPressed("lmouse") ~= true or ActiveGun.Auto == true then
		canShoot = true
	end
end

function update()
	_movement()
	_weaponLogic()

	

	
	

end