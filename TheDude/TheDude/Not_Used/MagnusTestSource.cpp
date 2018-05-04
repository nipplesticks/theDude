#ifdef _DEBUG
#pragma comment(lib, "LuaLibd.lib")
#else
#pragma comment(lib, "Lualib.lib")
#endif

#include <lua.hpp>
#include <SFML\Graphics.hpp>
#include <Windows.h>
#include <iostream>
#include <thread>
#include "lua.h"
#include <chrono>

#include "Camera\Camera.hpp"
#include "Level\Level.hpp"
#include "States\MainMenu.hpp"

#include <fstream>
#include "Interface\Button.hpp"

static int luaSleep(lua_State* L)
{
	int time = lua_tointeger(L, -1);
	lua_pop(L, -1);
	lua_pushnumber(L, 10);
	Sleep(time);
	return 1;
}


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	int counter = 0;

	lua_pushcfunction(L, luaSleep);
	lua_setglobal(L, "luaSleep");

	while (!GetAsyncKeyState(VK_ESCAPE))
	{
		int error = luaL_loadfile(L, "test.Lua") || lua_pcall(L, 0, 0, 0);
		if (error)
		{
			std::cout << lua_tostring(L, -1) << '\n';
			lua_pop(L, -1);
		}

		lua_getglobal(L, "add");
		lua_pushnumber(L, 10.3f);
		lua_pushnumber(L, 10.6f);
		error = lua_pcall(L, 2, 1, 0);
		float number = lua_tonumber(L, 1);
		lua_pop(L, -1);
		
		lua_getglobal(L, "logic");
		error = lua_pcall(L, 0, 0, 0);
		if (error)
		{
			std::cout << lua_tostring(L, -1) << '\n';
			lua_pop(L, -1);
		}
		
		int i = lua_gettop(L);
		
		//system("cls");
		//printf("\r Result: %f, Counter: %d, Stack: %d", number, counter++, i);

	}
	
	lua_close(L);

	return 0;
}