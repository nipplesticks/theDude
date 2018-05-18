#pragma once
#include "../OurLua/OurLua.hpp"
#include "State.hpp"
#include "../Entity/Character.hpp"
#include "../Level/Level.hpp"
#include "../Entity/Weapon.hpp"
#include <Windows.h>

#include <iostream>
#include <vector>
#include <string>


class Game : public State
{
private:
	OurLua * m_entityHandler;
	static bool s_isGameRunning;
	Level m_level; 
public:
	Game(std::string level);
	~Game();
	void Update() override;
	void Draw() override;

private:
// Help Functions
	void _init(std::string level);
	void _initEntityHandler(std::string luaFile);
	void _pushFunctions();

public:
// Lua Functions
	LUA_FUNC s_isKeyPressed(lua_State * l);
	LUA_FUNC s_CheckCollision(lua_State * l);
	LUA_FUNC s_ExitGame(lua_State * l);
	LUA_FUNC s_setPlayerPos(lua_State * l);
	LUA_FUNC s_mapCol(lua_State* l);
};
