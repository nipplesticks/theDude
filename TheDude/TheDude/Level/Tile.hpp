#pragma once
#include <SFML\Graphics.hpp>

class Tile : public sf::Drawable
{
public:
	enum Type
	{
		Water,
		Ground,
		Wall
	};

private:
	sf::RectangleShape	m_tileShape;
	sf::Vector2i		m_pos;
	int					m_type;

public:
	Tile(float sizeX = 16, float sizeY = 16, int type = 0);
	Tile(const Tile & other);
	virtual ~Tile() {};

	void setPosition(float x, float y);
	void setPosition(const sf::Vector2f &position);
	void setSize(float x, float y);
	void setSize(const sf::Vector2f &size);
	void setType(int type);
	void setColor(int r, int g, int b);
	void setColor(const sf::Color &color);

	int getType() const;
	const sf::Vector2f& getSize() const;
	const sf::Vector2i& getPosition() const;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	Tile& operator=(const Tile & other);

private:
	void _copy(const Tile & other);
	void _cleanup();


};