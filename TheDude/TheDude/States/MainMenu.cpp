#include "MainMenu.hpp"

MainMenu::MainMenu()
{
	sf::Vector2u p = s_window->getSize();

	sf::Vector2f size(100, 100);

	rs.setPosition((p.x / 2) - size.x / 2, (p.y / 2) - size.y / 2);
	rs.setSize(size);
	rs.setFillColor(sf::Color::Magenta);

}

void MainMenu::Update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	{
		Push(new GameState("Resourses/Levels/test.chef"));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
	{
		Pop();
	}
}

void MainMenu::Draw()
{
	s_window->draw(rs);
}
