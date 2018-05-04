#include "Item.hpp"

Item::Item(sf::Vector2f position, sf::Color color,sf::Vector2f speed, std::string effectType) : Entity()
{
	m_isPicked = false; 
	setEffect(effectType); 
}

Item::Item(float x, float y, sf::Color color, float speedX, float speedY, std::string effectType) : Entity()
{
	m_isPicked = false; 
	setEffect(effectType); 
}

Item::Item(float x, float y, sf::Color color, float speed, std::string effectType) : Entity()
{
	m_isPicked = false; 
	setEffect(effectType); 
}

Item::Item()
{

}

Item::~Item()
{
}

bool Item::getIsPicked() const
{
	return m_isPicked; 
}

Item::Effect Item::getEffect() const
{
	return m_effect; 
}

void Item::setIsPicked(bool isPicked) 
{
	m_isPicked = isPicked;
}

void Item::setEffect(std::string effectType)
{
	if (effectType == "HP")
	{
		m_effect = HP; 
	}
	else if (effectType == "SPEEDINCREASE")
	{
		m_effect = SPEEDINCREASE; 
	}
	else if (effectType == "DAMAGEINCREASE")
	{
		m_effect = DAMAGEINCREASE; 
	}
	else
	{
		m_effect = UNDEFINED; 
	}
}

void Item::Update()
{
	//Entity::update(dt); 
}
