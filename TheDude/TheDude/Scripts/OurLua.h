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
#include <vector>

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
	void PushFunctions();
	void PushClassFunctions(const std::string& metaName, luaL_Reg functions[], void(*target), const std::string& luaClassName);
	void PushClassFunction(void(*target), int(*function)(lua_State* L), const std::string & name);
	
	
	static std::vector<int> GetIntegers(lua_State * L, int n)
	{
		
		std::vector<int> r;
		for (int i = 0; i < n; ++i)
		{
			if (lua_isnumber(L, -1))
			{
			
				r.push_back(lua_tointeger(L, -1));
				lua_pop(L, -1);
				
			}

		}
		
		return r;
	}
	template <typename T>
	static T* getClassPointer(lua_State * l);


	void Update();
private:
	void _updateScript();
	void _handleError();

};
template<typename T>
inline T* OurLua::getClassPointer(lua_State * l)
{
	T* r = static_cast<T*>(lua_touserdata(l,lua_upvalueindex(1)));
	return r;
}