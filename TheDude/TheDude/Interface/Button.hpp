#pragma once
#include <SFML\Graphics.hpp>
#include <functional>

class Button : public sf::Drawable
{
private:
	static sf::Font s_font;
	static bool s_fontLoaded;
private:
	sf::RectangleShape					m_buttonShape;
	std::function<void()>				m_func;
	std::function<void(std::string)>	m_funcWithString;
	sf::Text							m_buttonText;
	bool m_hasFunc;
public:
	Button(int x, int y, int sizeX, int sizeY);
	bool Update(sf::Vector2i mousePos);

	
	void setFunctionPointer(std::function<void()> name, bool lvlBtn = false);
	
	void setButtonText(const sf::String &text, int size = 30);

	sf::RectangleShape& getShape();

	std::string getTextString() const;
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
