#pragma once
#include "../Entity/Enemy.h"
class EnemyController
{
private:
	int m_nrOfEnemies;
	int m_nrOfActive; 
	Enemy* m_enemies;

public:
	EnemyController(int nrOfEnemies);

	~EnemyController();

	void setup(int index, sf::Vector2f position, sf::Color color, sf::Vector2f speed, float attackStart, float defenceStart);
	void setup(int index, float x, float y, sf::Color color, float speedX, float speedY, float attackStart, float defenceStart);
	void setup(int index, float x, float y, sf::Color color, float speed, float attackStart, float defenceStart);

	void setAsInactive(int index);

	int getNrOfActive();

	void updateEnemies(float dt);
};

