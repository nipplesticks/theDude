#pragma once
#include "../OurLua/OurLua.hpp"
#include "Projectile.hpp"
#include <vector>

class Weapon
{
public:
	static std::string metaTable;
private:
	std::vector<Projectile*> bulletContainer;
	std::string	m_scriptPath;
public:
	Weapon(const std::string & script);
	~Weapon();
	void Shoot(float x, float y, float dx, float dy);
	void Update();
	void Draw(sf::RenderWindow * wnd, sf::Vector2f camPos);

	LUA_FUNC s_Create(lua_State* l);
	LUA_FUNC s_Destroy(lua_State* l);

	LUA_FUNC s_Shoot(lua_State* l);
};