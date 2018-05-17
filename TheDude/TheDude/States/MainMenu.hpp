#pragma once
#include "State.hpp"
#include "../Interface/Button.hpp"

class MainMenu : public State
{
private:
	Button * m_Game;
	Button * m_Editor;
	Button * m_Exit;

	sf::RectangleShape m_bck;
	sf::Texture m_t;
	int px_size;
	sf::Uint8 * px;
	float pxSizeX;
	float pxSizeY;

public:
	MainMenu();
	~MainMenu();

	void Update() override;
	void Draw() override;

private:
	void _init();
	void _pushGame();
	void _pushEditor();
	void _moveBackground();
};