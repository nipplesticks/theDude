#pragma once
#include <SFML\System\Vector2.hpp>


class Camera
{
private:
	sf::Vector2f m_pos;
	sf::Vector2f m_deltaPos;
	int m_winWidth;
	int m_winHeight;

	float m_speed;
public:
	Camera(float startX, float startY, int winWidth, int winHeight);

	void update();

	const sf::Vector2f& getPosition() const;
	const sf::Vector2f& getDeltaPosition() const;
	
};
