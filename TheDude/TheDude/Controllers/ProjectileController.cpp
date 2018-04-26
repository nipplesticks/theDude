#include "ProjectileController.hpp"

ProjectileController::ProjectileController()
{
	m_nrOfProjectiles = 0; 
	m_nrOfActive = 0; 
	m_projectiles.resize(m_nrOfProjectiles); 
}

ProjectileController::~ProjectileController()
{

}

void ProjectileController::setup(int index, sf::Vector2f position, sf::Color color, sf::Vector2f speed)
{
	m_projectiles[index] = Projectile(position, color, speed);
	m_nrOfActive++;
}

void ProjectileController::setup(int index, float x, float y, sf::Color color, float speedX, float speedY)
{
	m_projectiles[index] = Projectile(x,y,color,speedX,speedY);
	m_nrOfActive++;
}

void ProjectileController::setup(int index, float x, float y, sf::Color color, float speed)
{
	m_projectiles[index] = Projectile(x,y,color,speed);
	m_nrOfActive++; 
}

void ProjectileController::removeProjectileAt(int index)
{
	if (m_nrOfActive > 0)
	{
		m_projectiles.at(index).setIsActive(false); 
		m_nrOfActive--;
	}
}

int ProjectileController::getNrOfActive() const
{
	return m_nrOfActive; 
}

void ProjectileController::updateProjectiles(float dt)
{
	for (int i = 0; i < m_nrOfProjectiles; i++)
	{
		if (m_projectiles[i].getIsActive())
		{
			m_projectiles[i].update(dt);
		}
	}
}
