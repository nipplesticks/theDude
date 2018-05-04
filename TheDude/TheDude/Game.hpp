#pragma once
#include "OurLua/OurLua.hpp"
#include <iostream>
#include <vector>
#include <string>
#include "Entity\Character.hpp"
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