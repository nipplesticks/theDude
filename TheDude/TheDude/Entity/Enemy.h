#pragma once
#include "Character.hpp"
class Enemy : public Character
{
private:

public:
	Enemy(sf::Vector2f position, sf::Color color, sf::Vector2f speed, float attackStart, float defenceStart);
	Enemy(float x, float y, sf::Color color, float speedX, float speedY, float attackStart, float defenceStart); 
	Enemy(float x, float y, sf::Color color, float speed, float attackStart, float defenceStart); 
	Enemy();

	~Enemy(); 

	void update(float dt); 

};
