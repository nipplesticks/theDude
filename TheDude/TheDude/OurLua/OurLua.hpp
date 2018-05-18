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

#define LUA_FUNC static int

class OurLua
{
private:
	lua_State * m_ls;
	std::string m_fileName;
	time_t		m_lastModified;

public:
	OurLua(const std::string & script);
	~OurLua();
	void InitLua();
	void PushFunction(int(* function)(lua_State* L), const std::string & name);
	void PushClassFunctions(const std::string& metaName, luaL_Reg functions[], const std::string& luaClassName);
	void PushClassFunction(void(*target), int(*function)(lua_State* L), const std::string & name);
	void PushInstancePtr(void(*ptr), const std::string & name);


	static std::vector<int> getIntegers(lua_State * L, int n);
	static std::vector<std::string> getStrings(lua_State * L, int n);
	static std::vector<bool> getBoolean(lua_State * L, int n);
	static std::vector<float> getFloats(lua_State * L, int n);
	template <typename T>
	static std::vector<T*> getPtr(lua_State * L, int n);

	static void setIntegers(lua_State * L, const std::vector<int> & ints);
	static void setStrings(lua_State * L, const std::vector<std::string> &strings);
	static void setBooleans(lua_State * L, const std::vector<bool> & booleans);
	static void setFloats(lua_State * L, const std::vector<float> & floats);


	template <typename T>
	static T* getClassPointer(lua_State * l);
	
	template <typename Instance>
	static Instance* getInstanceOf(lua_State * l, int n, const std::string &meta);

	template <typename Instance>
	static Instance** createInstanceOf(lua_State* l, const std::string &meta);

	template <typename Instance>
	static std::vector<Instance**> getInstancePointer(lua_State* l, int amount);

	void Update();
	void Draw();
private:
	void _updateScript();
	void _handleError();

};
template<typename T>
inline std::vector<T*> OurLua::getPtr(lua_State * L, int n)
{
	std::vector<T*> r;
	for (int i = 0; i < n; i++)
	{
		r.push_back((T*)(lua_topointer(L, -(i + 1))));
	}

	return r;
}
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
	Instance** i = reinterpret_cast<Instance**>(lua_newuserdata(l, sizeof(Instance*)));

	luaL_getmetatable(l, meta.c_str());
	lua_setmetatable(l, -2);

	return i;
}

template<typename Instance>
inline std::vector<Instance**> OurLua::getInstancePointer(lua_State * l, int amount)
{
	std::vector<Instance**> instances;
	for (int i = 0; i < amount; i++)
		instances.push_back((Instance**)lua_touserdata(l, i + 1));


	return instances;
}
