#include "Character.hpp"

Character::Character(sf::Vector2f position, sf::Color color, sf::Vector2f speed, float attackStart, float defenceStart) : Entity(position, color, speed)
{
	m_health = 100.0f; 
	m_attacking = false; 
	m_attackStat = attackStart; 
	m_defenceStat = defenceStart; 
}

Character::Character(float x, float y, sf::Color color, float speedX, float speedY, float attackStart, float defenceStart) : Entity(x,y,color,speedX,speedY)
{
	m_health = 100.0f; 
	m_attacking = false; 
	m_attackStat = attackStart;
	m_defenceStat = defenceStart;
}

Character::Character(float x, float y, sf::Color color, float speed, float attackStart, float defenceStart) : Entity(x, y, color, speed)
{
	m_health = 100.0f; 
	m_attacking = false; 
	m_attackStat = attackStart;
	m_defenceStat = defenceStart;
}

Character::Character()
{

}

Character::~Character()
{
}

float Character::getHealth() const
{
	return m_health; 
}

bool Character::getAttacking() const
{
	return m_attacking; 
}

float Character::getAttackStat() const
{
	return m_attackStat; 
}

float Character::getDefenceStat() const
{
	return m_defenceStat; 
}

void Character::setHealth(float newHealth)
{
	m_health = newHealth; 
}

void Character::setAttacking(bool isAttacking)
{
	m_attacking = isAttacking; 
}

void Character::setAttackStat(float attackStat)
{
	m_attackStat = attackStat; 
}

void Character::setDefenceStat(float defenceStat)
{
	m_defenceStat = defenceStat; 
}

void Character::increaseAttack(float increaseStat)
{
	m_attackStat += increaseStat; 
}

void Character::increaseDefence(float increaseStat)
{
	m_defenceStat += increaseStat; 
}

void Character::decreaseAttack(float decreaseStat)
{
	m_attackStat -= decreaseStat; 
}

void Character::decreaseDefence(float decreaseStat)
{
	m_defenceStat -= decreaseStat; 
}

void Character::decreaseHP(float damage)
{
	m_health -= damage; 
}

void Character::attack()
{
	m_attacking = true; 
}

void Character::update(float dt)
{
	Entity::update(dt); 
}
