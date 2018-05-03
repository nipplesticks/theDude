#pragma once
#include "Scripts/OurLua.h"
#include <iostream>
#include <vector>
#include <string>
#include "Entity\Enemy.hpp"
#include "Entity\TheDude.h"
#include <Windows.h>
#include <SFML\Graphics.hpp>



class Game
{
private:
	sf::RenderWindow * p_wnd;
	OurLua * m_entityHandler;
	static bool s_isGameRunning;

public:
	Game();
	~Game();

	void Init(sf::RenderWindow * wnd);
	void update();
	void draw();

private:
// Help Functions
	void _init();
	void _initEntityHandler();
	void _pushFunctions();

public:
// Lua Functions
	LUA_FUNC isKeyPressed(lua_State * l);
	LUA_FUNC CheckCollision(lua_State * l);
	LUA_FUNC ExitGame(lua_State * l);
};