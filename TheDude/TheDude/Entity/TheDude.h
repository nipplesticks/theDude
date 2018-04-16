#pragma once
#include "Character.hpp"
class TheDude : public Character
{
private:

public:
	TheDude(sf::Vector2f position, sf::Color color, sf::Vector2f speed, float attackStart, float defenceStart); 
	TheDude(float x, float y, sf::Color color, float speedX, float speedY, float attackStart, float defenceStart);
	TheDude(float x, float y, sf::Color color, float speed, float attackStart, float defenceStart);
	TheDude(); 

	~TheDude(); 

	void update(float dt); 
};