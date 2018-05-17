#pragma once
#include <SFML\Graphics.hpp>
#include <functional>

class Button : public sf::Drawable
{
private:
	static sf::Font s_font;
	static bool s_fontLoaded;
private:
	sf::RectangleShape		m_buttonShape;
	std::function<void()>	m_func;
	sf::Text				m_buttonText;
public:
	Button(int x, int y, int sizeX, int sizeY);
	void Update(sf::Vector2i mousePos);

	
	void setFunctionPointer(std::function<void()> name);
	void setButtonText(const sf::String &text, int size = 30);

	sf::RectangleShape& getShape();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
