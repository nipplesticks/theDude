#include "Projectile.hpp"

Projectile::Projectile(float x, float y, float dx, float dy)
{
	m_script = nullptr;
	Entity::setPosition(x, y);

	//TEMP
	Entity::setSize(2, 2);
	Entity::setColor(255, 0, 0);
	//END

	m_dir.x = dx;
	m_dir.y = dy;
	m_damage = 0;
}

Projectile::~Projectile()
{
	delete m_script;
}

void Projectile::setScript(const std::string & script)
{
	if (m_script)
		delete m_script;
	m_script = new OurLua(script);
	_initLua();
}

bool Projectile::canTravel() const
{
	
	return false;
}

void Projectile::setDamage(int dmg)
{
	m_damage = dmg;
}

int Projectile::getDamage() const
{
	return m_damage;
}

void Projectile::Update()
{
	m_script->Update();
}

void Projectile::Draw()
{
	Entity::Draw();
}

void Projectile::_initLua()
{
	// Push Class Functions


	m_script->InitLua();
}
