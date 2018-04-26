#include "EnemyController.hpp"

EnemyController::EnemyController(int nrOfEnemies)
{
	m_nrOfEnemies = nrOfEnemies;
	m_nrOfActive = m_nrOfEnemies; 
	m_enemies = new Enemy[nrOfEnemies];
}

EnemyController::~EnemyController()
{
	delete[] m_enemies; 
}

void EnemyController::setup(int index, sf::Vector2f position, sf::Color color, sf::Vector2f speed, float attackStart, float defenceStart)
{
	m_enemies[index] = Enemy(position, color, speed, attackStart, defenceStart);
	m_nrOfActive++; 
}

void EnemyController::setup(int index, float x, float y, sf::Color color, float speedX, float speedY, float attackStart, float defenceStart)
{
	m_enemies[index] = Enemy(x, y, color, speedX, speedY, attackStart, defenceStart);
	m_nrOfActive++; 
}

void EnemyController::setup(int index, float x, float y, sf::Color color, float speed, float attackStart, float defenceStart)
{
	m_enemies[index] = Enemy(x, y, color, speed, attackStart, defenceStart); 
	m_nrOfActive++; 
}		

void EnemyController::setAsInactive(int index)
{
	if (m_nrOfActive > 0)
	{
		m_enemies[index].setIsActive(false);
		m_nrOfActive--; 
	}
}

int EnemyController::getNrOfActive()
{
	return m_nrOfActive;
}

void EnemyController::updateEnemies(float dt)
{
	for (int i = 0; i < m_nrOfEnemies; i++)
	{
		if (m_enemies[i].getIsActive())
		{
			m_enemies[i].update(dt);
		}
	}
}
