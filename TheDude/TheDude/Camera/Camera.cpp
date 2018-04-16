#include "Camera.hpp"
#include <SFML\Window\Keyboard.hpp>
#include <iostream>
Camera::Camera(float startX, float startY, int winWidth, int winHeight)
{
	m_pos.x = startX;
	m_pos.y = startY;
	m_speed = 2.0f;
	m_winHeight = winHeight;
	m_winWidth = winWidth;
	m_zoom = 1.0f;
}

void Camera::update()
{
	m_deltaPos = sf::Vector2f(0, 0);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		m_deltaPos.y -= -1 * m_speed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		m_deltaPos.y -= 1 * m_speed;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		m_deltaPos.x -= -1 * m_speed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		m_deltaPos.x -= 1 * m_speed;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C))
	{
		m_zoom -= 0.1f;
		if (m_zoom <= 0.0f) m_zoom = 0.1f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::V))
	{
		m_zoom += 0.1f;
		if (m_zoom >= 2.0f) m_zoom = 2.0f;
	}
	
	m_pos += m_deltaPos;
	
}

const sf::Vector2f & Camera::getPosition() const
{
	return m_pos;
}

const sf::Vector2f & Camera::getDeltaPosition() const
{
	return m_deltaPos;
}

float Camera::getZoom() const
{
	return m_zoom;
}
