#include "Projectile.hpp"

Projectile::Projectile(sf::Vector2f position, sf::Color color, sf::Vector2f speed) : Entity(position, color, speed)
{
	m_hasHit = false; 
}

Projectile::Projectile(float x, float y, sf::Color color, float speedX, float speedY) : Entity(x, y, color, speedX, speedY)
{
	m_hasHit = false; 
}

Projectile::Projectile(float x, float y, sf::Color color, float speed) : Entity(x, y, color, speed)
{
	m_hasHit = false; 
}

Projectile::Projectile()
{

}

Projectile::~Projectile()
{
}

bool Projectile::getHasHit() const
{
	return m_hasHit;
}

void Projectile::setHasHit(bool hasHit)
{
	m_hasHit = hasHit; 
}

void Projectile::update(float dt)
{
	//Entity::update(dt); 
}
