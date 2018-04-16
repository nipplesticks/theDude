#include "Tile.hpp"

Tile::Tile(float sizeX, float sizeY, Type type)
{
	this->setSize(sizeX, sizeY);
	this->setType(type);
}

Tile::Tile(const Tile & other)
{
	_cleanup();
	_copy(other);
}

void Tile::setPosition(float x, float y)
{
	setShapePosition(x, y);
	m_pos.x = x;
	m_pos.y = y;
}

void Tile::setPosition(const sf::Vector2f & position)
{
	m_tileShape.setPosition(position);
	m_pos.x = static_cast<int>(position.x + 0.5f);
	m_pos.y = static_cast<int>(position.y + 0.5f);
}

void Tile::setShapePosition(float x, float y)
{
	setShapePosition(sf::Vector2f(x, y));
}

void Tile::setShapePosition(const sf::Vector2f & position)
{
	m_tileShape.setPosition(position);
}

void Tile::setSize(float x, float y)
{
	m_tileShape.setSize(sf::Vector2f(x, y));
}

void Tile::setSize(const sf::Vector2f & size)
{
	m_tileShape.setSize(size);
}

void Tile::setType(const Type & type)
{
	m_type = type;

	switch (type)
	{
	case Type::Ground:
		this->setColor(sf::Color::Green);
			break;
	case Type::Wall:
		this->setColor(sf::Color::Yellow);
		break;
	case Type::Water:
		this->setColor(sf::Color::Blue);
		break;
	}
}

void Tile::setColor(float r, float g, float b)
{
	m_tileShape.setFillColor(sf::Color(r, g, b));
}

void Tile::setColor(const sf::Color & color)
{
	m_tileShape.setFillColor(color);
}

const Tile::Type & Tile::getType() const
{
	return m_type;
}

const sf::Vector2f & Tile::getSize() const
{
	return m_tileShape.getSize();
}

const sf::Vector2i & Tile::getPosition() const
{
	return m_pos;
}

const sf::Vector2f & Tile::getShapePosition() const
{
	return m_tileShape.getPosition();
}

void Tile::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_tileShape, states);
}



Tile & Tile::operator=(const Tile & other)
{
	if (this != &other)
	{
		_cleanup();
		_copy(other);
	}

	return *this;
}

void Tile::_copy(const Tile & other)
{
	m_type = other.m_type;
	m_tileShape = other.m_tileShape;
	m_pos = other.m_pos;
}

void Tile::_cleanup()
{
	// Implement if pointers


}
