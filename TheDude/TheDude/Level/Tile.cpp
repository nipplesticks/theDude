#include "Tile.hpp"

Tile::Tile(float sizeX, float sizeY, int type)
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
	m_tileShape.setPosition(x, y);
	m_pos.x = static_cast<int>(x);
	m_pos.y = static_cast<int>(y);
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

void Tile::setType(int type)
{
	m_type = type;
	ApplyTypeColor();
}

void Tile::setColor(int r, int g, int b)
{
	m_tileShape.setFillColor(sf::Color(static_cast<sf::Uint8>(r), static_cast<sf::Uint8>(g), static_cast<sf::Uint8>(b)));
}

void Tile::setColor(const sf::Color & color)
{
	m_tileShape.setFillColor(color);
}

void Tile::setTexture(const sf::Texture & texture, const sf::IntRect& rect)
{
	m_tileShape.setTexture(&texture);
	m_tileShape.setTextureRect(rect);
	m_tileShape.setFillColor(sf::Color::White);
}

const sf::Color & Tile::getColor() const
{
	return m_tileShape.getFillColor();
}

int Tile::getType() const
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

const sf::IntRect & Tile::getTextureRect() const
{
	return m_tileShape.getTextureRect();
}

void Tile::ApplyTypeColor()
{
	switch (m_type)
	{
	case Solid:
		m_tileShape.setFillColor(sf::Color::Blue);
		return;
	case None:
		m_tileShape.setFillColor(sf::Color::White);
		return;
	case Dangerous:
		m_tileShape.setFillColor(sf::Color::Red);
		return;
	}
}

void Tile::RemoveColors()
{
	m_tileShape.setFillColor(sf::Color::White);
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
