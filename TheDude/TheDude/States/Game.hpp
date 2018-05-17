#pragma once
#include "../OurLua/OurLua.hpp"
#include "State.hpp"
#include "../Entity/Character.hpp"
#include <Windows.h>

#include <iostream>
#include <vector>
#include <string>


class Game : public State
{
private:
	OurLua * m_entityHandler;
	static bool s_isGameRunning;
	bool** m_collisionArr;
	sf::IntRect rectArr[5];
public:
	Game();
	~Game();
	void Update() override;
	void Draw() override;
	bool** getCollisionArr();


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
