#pragma once
#include "GameState.hpp"


class MainMenu : public State
{
private:
	// HUD
	sf::RectangleShape rs; //temp

public:
	MainMenu();
	~MainMenu() {};

	void Update() override;
	void Draw() override;
};