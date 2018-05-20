#include "HeadsUpDisplay.h"

HeadsUpDisplay::HeadsUpDisplay()
{

}

HeadsUpDisplay::~HeadsUpDisplay()
{
}

sf::Font HeadsUpDisplay::getFont() const
{
	return m_headsUpFont; 
}

void HeadsUpDisplay::setFont(std::string fontPath, std::string fontText, sf::Vector2f position, int fontSize)
{
	if (m_headsUpFont.loadFromFile(fontPath))
	{
		m_fontText.setFont(m_headsUpFont);
		m_fontText.setString(fontText);
		m_fontText.setPosition(position);
		m_fontText.setCharacterSize(fontSize);
		m_fontText.setOutlineColor(sf::Color::Black); 
		m_fontText.setFillColor(sf::Color::Red);
	}
}

void HeadsUpDisplay::draw(sf::RenderTarget & renderTarget, sf::RenderStates states) const
{
	renderTarget.draw(m_fontText); 
}


