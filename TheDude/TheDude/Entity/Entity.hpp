#pragma once
#include <SFML/Graphics.hpp>
class Entity
{
private:
	sf::RectangleShape m_shape;
	sf::Vector2f m_position;
	sf::Texture m_texture;
public:
	Entity();
	virtual ~Entity() {};

	virtual void setColor(int r, int g, int b, int a = 255);
	virtual void setViewPos(sf::Vector2f viewPos);
	virtual void setPosition(float x, float y);

	virtual void Move(float x, float y);

	virtual void setSize(float x, float y);
	virtual void setOrigin(float x, float y);

	virtual void setSprite(const std::string& sprite);

	virtual const sf::Vector2f getPosition() const;
	virtual const sf::Vector2f getSize() const;
	virtual const sf::Color getColor() const;
	virtual const sf::RectangleShape& getShape() const;

	virtual void Update() = 0;
	virtual void Draw();
};