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
	void PushClassFunctions(const std::string& metaName, luaL_Reg functions[], const std::string& luaClassName);
	void PushClassFunction(void(*target), int(*function)(lua_State* L), const std::string & name);
	
	
	static std::vector<int> GetIntegers(lua_State * L, int n);
	static std::vector<std::string> GetStrings(lua_State * L, int n);
	static std::vector<bool> GetBoolean(lua_State * L, int n);
	static std::vector<float> GetFloats(lua_State * L, int n);


	template <typename T>
	static T* getClassPointer(lua_State * l);
	
	template <typename Instance>
	static Instance* getInstanceOf(lua_State * l, int n, const std::string &meta);

	template <typename Instance>
	static Instance** createInstanceOf(lua_State* l, const std::string &meta);

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

template<typename Instance>
inline Instance * OurLua::getInstanceOf(lua_State * l, int n, const std::string &meta)
{
	Instance* iPtr = nullptr;
	void * ptr = luaL_testudata(l, n, meta.c_str());
	if (ptr)
		iPtr = *(Instance**)ptr;
	return iPtr;
}

template<typename Instance>
inline Instance ** OurLua::createInstanceOf(lua_State* l, const std::string &meta)
{
	Instance** i = reinterpret_cast<Instance**>(lua_newuserData(l, sizeof(Instance*)));

	luaL_getmetatable(l, meta.c_str());
	lua_setmetatable(l, -2);

	return i;
}