#pragma once
#include "../Entity/Projectile.hpp"
#include <vector>
class ProjectileController
{
private:
	int m_nrOfProjectiles; 
	int m_nrOfActive; 
	std::vector<Projectile> m_projectiles; 
public:
	ProjectileController(); 
	~ProjectileController(); 

	void setup(int index, sf::Vector2f position, sf::Color color, sf::Vector2f speed); 
	void setup(int index, float x, float y, sf::Color color, float speedX, float speedY); 
	void setup(int index, float x, float y, sf::Color color, float speed); 

	void removeProjectileAt(int index); 

	int getNrOfActive() const; 

	void updateProjectiles(float dt); 
};