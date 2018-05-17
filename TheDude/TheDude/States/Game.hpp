#pragma once
#include <Windows.h>
#include "../OurLua/OurLua.hpp"
#include "State.hpp"
#include "../Entity/Character.hpp"

#include <iostream>
#include <vector>
#include <string>


class Game : public State
{
private:
	OurLua * m_entityHandler;
	static bool s_isGameRunning;
public:
	Game();
	~Game();

	void Update() override;
	void Draw() override;

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
	LUA_FUNC s_test(lua_State* l);
};