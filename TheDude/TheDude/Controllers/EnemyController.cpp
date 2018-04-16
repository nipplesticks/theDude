#include "EnemyController.hpp"

EnemyController::EnemyController(int nrOfEnemies)
{
	m_nrOfEnemies = nrOfEnemies;
	m_enemies = new Enemy*[nrOfEnemies];
	for (int i = 0; i < nrOfEnemies; i++)
	{
		m_enemies[i] = new Enemy();
	}
}

EnemyController::~EnemyController()
{
	for (int i = 0; i < m_nrOfEnemies; i++)
	{
		delete m_enemies[i];
	}
}

void EnemyController::setup(int index, sf::Vector2f position, sf::Color color, sf::Vector2f speed, float attackStart, float defenceStart)
{
	m_enemies[index]->setPosition(position);
	m_enemies[index]->setColor(color);
	m_enemies[index]->setSpeed(speed);
	m_enemies[index]->setAttackStat(attackStart);
	m_enemies[index]->setDefenceStat(defenceStart);
}

void EnemyController::setup(int index, float x, float y, sf::Color color, float speedX, float speedY, float attackStart, float defenceStart)
{
	m_enemies[index]->setPosition(x, y);
	m_enemies[index]->setColor(color);
	m_enemies[index]->setSpeed(speedX, speedY);
	m_enemies[index]->setAttackStat(attackStart);
	m_enemies[index]->setDefenceStat(defenceStart);
}

void EnemyController::setup(int index, float x, float y, sf::Color color, float speed, float attackStart, float defenceStart)
{
	m_enemies[index]->setPosition(x, y);
	m_enemies[index]->setColor(color);
	m_enemies[index]->setSpeed(speed);
	m_enemies[index]->setAttackStat(attackStart);
	m_enemies[index]->setDefenceStat(defenceStart);
}

void EnemyController::setAsInactive(int index)
{
	m_enemies[index]->setIsActive(false);
}

int EnemyController::getNrOfEnemies()
{
	return m_nrOfEnemies;
}

void EnemyController::updateEnemies(float dt)
{
	for (int i = 0; i < m_nrOfEnemies; i++)
	{
		if (m_enemies[i]->getIsAvtive())
		{
			m_enemies[i]->update(dt);
		}
	}
}
