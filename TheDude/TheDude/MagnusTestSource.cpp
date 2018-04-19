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

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);
	


	
	system("PAUSE");
	return 0;
}