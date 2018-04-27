#pragma once
#include "Entity.hpp"
class Projectile : public Entity
{
private:
	bool m_hasHit; 
public:
	Projectile(sf::Vector2f position, sf::Color color, sf::Vector2f speed); 
	Projectile(float x, float y, sf::Color color, float speedX, float speedY); 
	Projectile(float x, float y, sf::Color color, float speed); 
	Projectile(); 

	~Projectile();

	bool getHasHit() const; 

	void setHasHit(bool hasHit); 

	void update(float dt) override; 
}; 
