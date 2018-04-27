#pragma once
#include "Entity.hpp"
class Item : public Entity
{
private:
	bool m_isPicked; 
	enum Effect
	{
		HP,
		SPEEDINCREASE, 
		DAMAGEINCREASE, 
		UNDEFINED
	};
	Effect m_effect; 

public:
	Item(sf::Vector2f position, sf::Color color, sf::Vector2f speed, std::string effectType);
	Item(float x, float y, sf::Color color, float speedX, float speedY, std::string effectType); 
	Item(float x, float y, sf::Color color, float speed, std::string effectType);
	Item(); 

	~Item(); 

	bool getIsPicked() const; 
	Effect getEffect() const; 

	void update(float dt) override;

	void setIsPicked(bool isPicked); 
	void setEffect(std::string effectType); 

};
