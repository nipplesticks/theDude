#include "ItemController.h"

ItemController::ItemController(int nrOfItems)
{
	m_nrOfItems = nrOfItems; 
	m_items = new Item[m_nrOfItems]; 
}

ItemController::~ItemController()
{
	delete[] m_items; 
}

void ItemController::setup(int index, sf::Vector2f position, sf::Color color, sf::Vector2f speed, std::string effectType)
{
	m_items[index] = Item(position, color, speed, effectType); 
}

void ItemController::setup(int index, float x, float y, sf::Color color, float speedX, float speedY, std::string effectType)
{
	m_items[index] = Item(x,y,color,speedX,speedY,effectType);
}

void ItemController::setup(int index, float x, float y, sf::Color color, float speed, std::string effectType)
{
	m_items[index] = Item(x, y, color, speed, effectType); 
}

void ItemController::setAsInactive(int index)
{
	m_items[index].
}
