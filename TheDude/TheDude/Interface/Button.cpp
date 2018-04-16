#include "Button.hpp"

Button::Button(int x, int y, int sizeX, int sizeY)
{
	m_buttonShape.setPosition(x, y);
	m_buttonShape.setSize(sf::Vector2f(sizeX, sizeY));
	m_buttonShape.setFillColor(sf::Color::Yellow);
}

void Button::update(sf::Vector2i mousePos)
{
	sf::Vector2f points[4];
	points[0] = m_buttonShape.getPosition();
	points[1] = sf::Vector2f(m_buttonShape.getPosition().x + m_buttonShape.getSize().x, m_buttonShape.getPosition().y);
	points[2] = m_buttonShape.getPosition() + m_buttonShape.getSize();
	points[3] = sf::Vector2f(m_buttonShape.getPosition().x, m_buttonShape.getPosition().y + m_buttonShape.getSize().y);

	if (mousePos.x > points[0].x && mousePos.x < points[1].x && mousePos.y > points[0].y && mousePos.y < points[3].y)
	{
		m_buttonShape.setOutlineThickness(5.0f);
		m_buttonShape.setOutlineColor(sf::Color::Black);
		m_function();
	}
	else
	{
		m_buttonShape.setOutlineThickness(0.0f);
	}
}

void Button::setFunctionPointer(void (*func)())
{
	m_function = func;
}

void Button::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_buttonShape);
}
