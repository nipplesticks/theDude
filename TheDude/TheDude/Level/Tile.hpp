#pragma once
#include <SFML\Graphics.hpp>

#define TYPE_NONE_COLOR sf::Color::White
#define TYPE_DANGEROUS_COLOR sf::Color::Red
#define TYPE_SOLID_COLOR sf::Color::Blue
#define TYPE_GOAL_COLOR sf::Color::Yellow


class Tile : public sf::Drawable
{
public:
	enum Type
	{
		None,
		Dangerous,
		Solid,
		Goal
	};

private:
	sf::RectangleShape	m_tileShape;
	sf::Vector2i		m_pos;
	sf::Vector2f		m_scale;
	int					m_type;
	sf::Color		m_tempColor;

public:
	Tile(float sizeX = 16, float sizeY = 16, int type = 0);
	Tile(const Tile & other);
	virtual ~Tile() {};

	void setPosition(float x, float y);
	void setPosition(const sf::Vector2f &position);
	void setShapePosition(float x, float y);
	void setShapePosition(const sf::Vector2f& position);

	void setSize(float x, float y);
	void setSize(const sf::Vector2f &size);
	void setType(int type);
	void setColor(int r, int g, int b, bool permCol);
	void setColor(const sf::Color &color, bool permanant = false);
	void setTexture(const sf::Texture & texture, const sf::IntRect& rect);
	
	const sf::Color& getColor() const;
	const sf::Color& getOutlineColor() const;

	int getType() const;
	const sf::Vector2f& getSize() const;
	const sf::Vector2i& getPosition() const;
	const sf::Vector2f& getShapePosition() const;
	const sf::IntRect& getTextureRect() const;

	void ApplyTypeColor(bool on);
	void RemoveColors();
	void RemoveTexture();
	bool hasTexture() const;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	Tile& operator=(const Tile & other);

private:
	void _copy(const Tile & other);
	void _cleanup();


};