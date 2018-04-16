#pragma once
#include <SFML\Graphics.hpp>

class Tile : public sf::Drawable
{
public:
	enum Type
	{
		Ground,
		Wall,
		Water
	};

private:
	sf::RectangleShape	m_tileShape;
	Type				m_type;

public:
	Tile(float sizeX = 16, float sizeY = 16, Type type = Type::Water);
	virtual ~Tile() {};

	void setPosition(float x, float y);
	void setPosition(const sf::Vector2f &position);
	void setSize(float x, float y);
	void setSize(const sf::Vector2f &size);
	void setType(const Type &type);
	void setColor(float r, float g, float b);
	void setColor(const sf::Color &color);

	const Type & getType() const;
	const sf::Vector2f& getSize() const;
	const sf::Vector2f& getPosition() const;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};