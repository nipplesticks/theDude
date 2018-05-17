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
	bool** m_collisionArr;
	sf::IntRect rectArr[5];
public:
	int value = 1;
	Game();
	~Game();

	bool** getCollisionArr(); 
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
	LUA_FUNC s_isKeyPressed(lua_State * l);
	LUA_FUNC s_CheckCollision(lua_State * l);
	LUA_FUNC s_ExitGame(lua_State * l);
	LUA_FUNC s_setPlayerPos(lua_State * l);
	LUA_FUNC s_mapCol(lua_State* l);
};