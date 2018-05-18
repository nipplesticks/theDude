#include "Weapon.hpp"

std::vector<Projectile*>* Weapon::s_bulletContainer = new std::vector<Projectile*>;

Weapon::Weapon(int dmg, int speed, int range)
{
	m_scriptPath = "";
	m_damage = dmg;
	m_speed = speed;
	m_range = range;
}

Weapon::~Weapon()
{

}

void Weapon::setLogic(const std::string & path)
{
	m_scriptPath = path;
}

void Weapon::Shoot(float x, float y, float dx, float dy)
{
	Projectile* p = new Projectile(x, y, dx, dy);
	p->setScript(m_scriptPath);
	s_bulletContainer->push_back(p);
}
