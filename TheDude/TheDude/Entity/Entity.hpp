#pragma once
#include "../RenderQueue.h"
class Entity : public sf::Drawable
{
private:
	sf::Vector2f m_speed;
	sf::RectangleShape m_self;
	sf::Vector2f m_position;
	sf::Color m_color;
	bool m_isActive;

public:
	Entity(sf::Vector2f position, sf::Color color, sf::Vector2f speed);
	Entity(float x, float y, sf::Color color, float speedX, float speedY);
	Entity(float x, float y, sf::Color color, float speed);
	Entity();

	~Entity();

	virtual void update(float dt);

	sf::Vector2f getPosition() const;
	sf::Vector2f getSpeed() const;
	sf::RectangleShape& getSelf();
	sf::Color getColor() const;
	bool getIsActive() const;

	void setPosition(float x, float y);
	void setPosition(sf::Vector2f newPosXY);
	void setSpeed(float x, float y);
	void setSpeed(sf::Vector2f newSpeedXY);
	void setSpeed(float newSpeed);
	void setIsActive(bool isActive);

	void setColor(sf::Color color);

	void move(float x, float y);
	void move(sf::Vector2f moveXY);

	bool checkIntersection() const;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void draw();
};