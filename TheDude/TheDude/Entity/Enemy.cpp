#include "Enemy.h"

Enemy::Enemy(sf::Vector2f position, sf::Color color, sf::Vector2f speed, float attackStart, float defenceStart) : Character(position, color, speed, attackStart, defenceStart)
{
}

Enemy::Enemy(float x, float y, sf::Color color, float speedX, float speedY, float attackStart, float defenceStart) : Character(x,y,color,speedX,speedY,attackStart,defenceStart)
{
}

Enemy::Enemy(float x, float y, sf::Color color, float speed, float attackStart, float defenceStart) : Character(x,y,color,speed,attackStart,defenceStart)
{
}

Enemy::~Enemy()
{
}

void Enemy::update(float dt)
{
	Character::update(dt); 
}
