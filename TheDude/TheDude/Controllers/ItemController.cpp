#include "ItemController.hpp"

ItemController::ItemController(int nrOfItems)
{
	m_nrOfItems = nrOfItems; 
	m_nrOfActive = nrOfItems; 
	m_items = new Item[m_nrOfItems]; 
}

ItemController::~ItemController()
{
	delete[] m_items; 
}

void ItemController::setup(int index, sf::Vector2f position, sf::Color color, sf::Vector2f speed, std::string effectType)
{
	m_items[index] = Item(position, color, speed, effectType); 
	m_nrOfActive++;
}

void ItemController::setup(int index, float x, float y, sf::Color color, float speedX, float speedY, std::string effectType)
{
	m_items[index] = Item(x,y,color,speedX,speedY,effectType);
	m_nrOfActive++; 
}

void ItemController::setup(int index, float x, float y, sf::Color color, float speed, std::string effectType)
{
	m_items[index] = Item(x, y, color, speed, effectType); 
	m_nrOfActive++; 
}

void ItemController::setAsInactive(int index)
{
	if (m_nrOfActive > 0)
	{
		m_items[index].setIsActive(false); 
		m_nrOfActive--; 
	}
}

int ItemController::getNrOfActive() const
{
	return m_nrOfActive; 
}

void ItemController::updateItems(float dt)
{
	for (int i = 0; i < m_nrOfItems; i++)
	{
		if (m_items[i].getIsActive())
		{
			m_items[i].update(dt); 
		}
	}
}
