#include "TheDude.h"

TheDude::TheDude(sf::Vector2f position, sf::Color color, sf::Vector2f speed, float attackStart, float defenceStart) : Character(position, color, speed, attackStart, defenceStart)
{

}

TheDude::TheDude(float x, float y, sf::Color color, float speedX, float speedY, float attackStart, float defenceStart) : Character(x,y,color,speedX,speedY, attackStart, defenceStart)
{
}

TheDude::TheDude(float x, float y, sf::Color color, float speed, float attackStart, float defenceStart) : Character(x, y, color, speed, attackStart, defenceStart)
{
}

TheDude::~TheDude()
{
}

void TheDude::update(float dt)
{
	Character::update(dt); 
}
