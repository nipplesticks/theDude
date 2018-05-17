#include "Button.hpp"
#include "../RenderQueue.hpp"

bool Button::s_fontLoaded = false;
sf::Font Button::s_font;

Button::Button(int x, int y, int sizeX, int sizeY)
{
	m_buttonShape.setPosition(static_cast<float>(x), static_cast<float>(y));
	m_buttonShape.setSize(sf::Vector2f(static_cast<float>(sizeX), static_cast<float>(sizeY)));
	m_buttonShape.setFillColor(sf::Color::Yellow);
	
	bool lol;
	if (!s_fontLoaded)
	{
		lol = s_font.loadFromFile("Resourses/FONT/Hollywood Capital Hills (Final).ttf");
		s_fontLoaded = true;
	}

	m_buttonText.setFont(s_font);
	m_buttonText.setFillColor(sf::Color::Black);
	m_buttonText.setPosition(static_cast<float>(x), static_cast<float>(y));
}

void Button::Update(sf::Vector2i mousePos)
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
		m_buttonText.setFillColor(sf::Color::Blue);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			m_func();
	}
	else
	{
		m_buttonShape.setOutlineThickness(0.0f);
		m_buttonText.setFillColor(sf::Color::Black);
	}
}


void Button::setFunctionPointer(std::function<void()> name)
{
	m_func = name;
}

void Button::setButtonText(const sf::String & text, int size)
{
	m_buttonText.setCharacterSize(size);
	m_buttonText.setString(text);
	m_buttonText.setPosition(m_buttonShape.getPosition() + (m_buttonShape.getSize() / 2.0f));
	m_buttonText.setOrigin(m_buttonText.getLocalBounds().width * 0.5f, m_buttonText.getLocalBounds().height * 0.5f);
}

sf::RectangleShape & Button::getShape()
{
	return m_buttonShape;
}

void Button::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_buttonShape);
	target.draw(m_buttonText);
}
