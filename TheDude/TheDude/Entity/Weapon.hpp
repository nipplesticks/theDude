#pragma once
#include "../OurLua/OurLua.hpp"
#include "Projectile.hpp"
#include <vector>

class Weapon
{
public:
	static std::vector<Projectile*>* s_bulletContainer;

private:
	std::string	m_scriptPath;
	int			m_damage;
	int			m_speed;
	int			m_range;

public:
	Weapon(int dmg = 1, int speed = 2, int range = -1);
	~Weapon();
	void setLogic(const std::string & path);
	void Shoot(float x, float y, float dx, float dy);
};