#pragma once
#include "../Entity/Item.hpp"
class ItemController
{
private:
	int m_nrOfItems; 
	Item* m_items;
public:
	ItemController(int nrOfItems); 
	~ItemController(); 

	void setup(int index, sf::Vector2f position, sf::Color color, sf::Vector2f speed, std::string effectType);
	void setup(int index, float x, float y, sf::Color color, float speedX, float speedY, std::string effectType);
	void setup(int index, float x, float y, sf::Color color, float speed, std::string effectType);

	void setAsInactive(int index); 

	void updateItems(float dt); 

};