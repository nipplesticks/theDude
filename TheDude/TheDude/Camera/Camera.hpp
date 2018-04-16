#pragma once
#include <SFML\System\Vector2.hpp>


class Camera
{
private:
	sf::Vector2f m_pos;
	sf::Vector2f m_deltaPos;

	float m_speed;
public:
	Camera(float startX, float startY);

	void update();

	const sf::Vector2f& getPosition() const;
	const sf::Vector2f& getDeltaPosition() const;
	
};
