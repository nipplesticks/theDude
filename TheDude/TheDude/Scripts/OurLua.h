#pragma once
#ifdef _DEBUG
#pragma comment(lib, "LuaLibd.lib")
#else
#pragma comment(lib, "Lualib.lib")
#endif

#include <lua.hpp>
#include "lua.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <string>

class OurLua
{
private:
	lua_State * m_ls;
	std::string m_fileName;
	time_t		m_lastModified;

public:
	OurLua(const std::string & script);
	void InitLua();

	void PushFunction(int(* function)(lua_State* L), const std::string & name);
	void PushClassFunction(void(*target), int(*function)(lua_State* L), const std::string & name);
	
	static int GetDataFromLua(lua_State * L, void(*&target));


	void Update();
private:
	void _updateScript();
	void _handleError();

};