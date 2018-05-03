#include "Entity.hpp"
#include "../RenderQueue.hpp"

Entity::Entity()
{
	m_shape.setPosition(0.0f, 0.0f);
	m_shape.setFillColor(sf::Color(255, 255, 255));
	m_shape.setSize(sf::Vector2f(100.0, 100.0));
	m_position.x = 0.0f;
	m_position.y = 0.0f;
}

void Entity::setColor(int r, int g, int b, int a)
{
	m_shape.setFillColor(sf::Color(r, g, b, a));
}

void Entity::setViewPos(sf::Vector2f viewPos)
{
	m_shape.setPosition(viewPos);
}

void Entity::setPosition(float x, float y)
{
	m_position.x = x;
	m_position.y = y;
}

void Entity::Move(float x, float y)
{
	m_position.x += x;
	m_position.y += y;
}

void Entity::setSize(float x, float y)
{
	m_shape.setSize(sf::Vector2f(x, y));
}

void Entity::setOrigin(float x, float y)
{
	m_shape.setOrigin(x, y);
}

const sf::Vector2f Entity::getPosition() const
{
	return m_position;
}

const sf::Vector2f Entity::getSize() const
{
	return m_shape.getSize();
}

const sf::Color Entity::getColor() const
{
	return m_shape.getFillColor();
}

const sf::RectangleShape & Entity::getShape() const
{
	return m_shape;
}

void Entity::Draw()
{
	Render::g_renderQueue.push_back(this);
}