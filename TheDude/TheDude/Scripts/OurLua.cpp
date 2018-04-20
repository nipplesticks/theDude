#include "OurLua.h"
#include <iostream>
#include <Windows.h>
OurLua::OurLua(const std::string & script)
{
	m_fileName = script;
	struct stat result;
	if (stat(m_fileName.c_str(), &result) == 0)
		m_lastModified = result.st_mtime;
	m_ls = luaL_newstate();
	luaL_openlibs(m_ls);

	int error = luaL_loadfile(m_ls, m_fileName.c_str()) || lua_pcall(m_ls, 0, 0, 0);
	if (error)
		_handleError();
	else
	{
		std::cout << m_fileName << " Opened\n";
	}
}

void OurLua::PushFunction(int(*function)(lua_State* L), const std::string & name)
{
	lua_pushcfunction(m_ls, function);
	lua_setglobal(m_ls, name.c_str());
}

void OurLua::PushClassFunction(void(*target), int(*function)(lua_State *L), const std::string & name)
{
	lua_pushlightuserdata(m_ls, target);
	lua_pushcclosure(m_ls, function, 1);
	lua_setglobal(m_ls, name.c_str());
}

int OurLua::GetDataFromLua(lua_State * L, void(*&target))
{
	target = lua_touserdata(L, lua_upvalueindex(1));
	int result = lua_tointeger(L, -1);
	lua_pop(L, 2);
	return result;
}

void OurLua::Update()
{
	_updateScript();
	lua_getglobal(m_ls, "update");
	int error = lua_pcall(m_ls, 0, 0, 0);
	if (error)
		_handleError();
}

void OurLua::_updateScript()
{
	struct stat result;
	if (stat(m_fileName.c_str(), &result) == 0)
	{
		time_t mod_time = result.st_mtime;
		if (mod_time != m_lastModified)
		{
			m_lastModified = mod_time;
			
			int error = 1;
			for (int i = 0; i < 3 && error == 1; i++)
			{
				error = luaL_loadfile(m_ls, m_fileName.c_str()) || lua_pcall(m_ls, 0, 0, 0);
				if (error)
				{
					_handleError();
					std::cout << "Retry no. [" << i + 1 << "]\n";
					Sleep(15);
				}
				else
				{
					std::cout << m_fileName << " Opened\n";
				}
				
			}
		}
	}
}

void OurLua::InitLua()
{
	lua_getglobal(m_ls, "init");
	int error = lua_pcall(m_ls, 0, 0, 0);
	if (error)
		_handleError();

}

void OurLua::_handleError()
{
	std::cout << lua_tostring(m_ls, -1) << '\n';
	lua_pop(m_ls, -1);
}

