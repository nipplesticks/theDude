#pragma once
#include "State.hpp"
#include "../Interface/Button.hpp"

class MainMenu : public State
{
private:
	Button * m_Game;
	Button * m_Editor;
	Button * m_Exit;

	bool m_showLevels;
	std::vector<Button*> m_levelButton;
	Button * m_returnToMM;
	


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
	void _displayLevels();
	void _disableShowLevels();
	void _pushGame(std::string level);
	void _pushEditor();
	void _moveBackground();
	std::vector<std::string> getfilesInDir();
};