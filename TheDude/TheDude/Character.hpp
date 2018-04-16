#pragma once
#include "Entity.hpp"
class Character : public Entity
{
private:
	float m_health; 
	float m_attackStat; 
	float m_defenceStat; 
	bool m_attacking; 

public:
	Character(sf::Vector2f position, sf::Color color,sf::Vector2f speed, float attackStart, float defenceStart); 
	Character(float x, float y, sf::Color color, float speedX, float speedy, float attackStart, float defenceStart);
	Character(float x, float y, sf::Color color, float speed, float attackStart, float defenceStart);
	
	~Character(); 

	float getHealth() const; 
	bool getAttacking() const; 
	float getAttackStat() const; 
	float getDefenceStat() const; 

	void setHealth(float newHealth); 
	void setAttacking(bool isAttacking); 
	void setAttackStat(float attackStat); 
	void setDefenceStat(float defenceStat); 
	
	void increaseAttack(float increaseStat); 
	void increaseDefence(float increaseStat); 
	void decreaseAttack(float decreaseStat); 
	void decreaseDefence(float decreaseStat); 
	
	void decreaseHP(float damage); 
	void attack(); 

	void update(float dt); 
};
