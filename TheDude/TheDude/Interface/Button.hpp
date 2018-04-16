#pragma once
#include <SFML\Graphics.hpp>

class Button : public sf::Drawable
{
private:
	sf::RectangleShape	m_buttonShape;
	void				(*m_function)();
public:
	Button(int x, int y, int sizeX, int sizeY);

	void update(sf::Vector2i mousePos);

	void setFunctionPointer(void(*func)());
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};