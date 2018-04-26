#include "Entity.hpp"

Entity::Entity(sf::Vector2f position, sf::Color color, sf::Vector2f speed)
{
	m_self.setPosition(position);
	m_self.setFillColor(color);
	setSpeed(speed);
	m_position = position;
}

Entity::Entity(float x, float y, sf::Color color, float speedX, float speedY)
{
	m_self.setPosition(sf::Vector2f(x, y));
	m_self.setFillColor(color);
	setSpeed(sf::Vector2f(speedX, speedY));
	m_position = sf::Vector2f(x, y);
}

Entity::Entity(float x, float y, sf::Color color, float speed)
{
	m_self.setPosition(sf::Vector2f(x, y));
	m_self.setFillColor(color);
	setSpeed(sf::Vector2f(speed, speed));
	m_position = sf::Vector2f(x, y);
}

Entity::Entity()
{
	m_self.setPosition(sf::Vector2f(0, 0));
	m_self.setFillColor(sf::Color::Blue);
	m_self.setSize(sf::Vector2f(100, 100));
}

Entity::~Entity()
{
}

void Entity::update(float dt)
{
	m_self.move(m_speed.x, m_speed.y);
	m_position = m_position + m_speed;
}

sf::Vector2f Entity::getPosition() const
{
	return m_self.getPosition();
}

sf::Vector2f Entity::getSpeed() const
{
	return m_speed;
}

sf::RectangleShape& Entity::getSelf()
{
	return m_self;
}

sf::Color Entity::getColor() const
{
	return m_color;
}

bool Entity::getIsActive() const
{
	return m_isActive;
}

void Entity::setPosition(float x, float y)
{
	m_self.setPosition(sf::Vector2f(x, y));
	m_position = sf::Vector2f(x, y);
}

void Entity::setPosition(sf::Vector2f newPosXY)
{
	m_self.setPosition(newPosXY);
	m_position = sf::Vector2f(newPosXY);
}

void Entity::setSpeed(float x, float y)
{
	m_speed.x = x;
	m_speed.y = y;
}

void Entity::setSpeed(sf::Vector2f newSpeedXY)
{
	m_speed = sf::Vector2f(newSpeedXY);
}

void Entity::setSpeed(float newSpeed)
{
	m_speed = sf::Vector2f(newSpeed, newSpeed);
}

void Entity::setIsActive(bool isActive)
{
	m_isActive = isActive;
}

void Entity::setColor(sf::Color color)
{
	m_color = color;
	m_self.setFillColor(m_color);
}

void Entity::move(float x, float y)
{
	m_self.move(sf::Vector2f(x, y));
}

void Entity::move(sf::Vector2f moveXY)
{
	m_self.move(moveXY);
}

bool Entity::checkIntersection() const
{
	return false;
}

void Entity::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_self);
}

void Entity::draw()
{
	Render::renderQueue.push_back(&m_self);
}
