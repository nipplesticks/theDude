#pragma once
#include <SFML\Graphics.hpp>

class HeadsUpDisplay : public sf::Drawable
{
private:
	sf::Font m_headsUpFont; 
	sf::Text m_fontText; 
public:
	HeadsUpDisplay();
	~HeadsUpDisplay(); 

	sf::Font getFont() const; 

	void setFont(std::string fontPath, std::string fontText, sf::Vector2f position, int fontSize);

	void draw(sf::RenderTarget& renderTarget, sf::RenderStates states) const; 
};
