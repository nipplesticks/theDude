#pragma once
#include "Entity.hpp"
#include "../OurLua/OurLua.hpp"
class Projectile : public Entity
{
public:
	static std::string metaTable;

private:
	OurLua * m_script;
	sf::Vector2f m_dir;
	int m_damage;
	bool m_active;

public:
	Projectile(float x, float y, float dx, float dy);
	~Projectile();
	void setScript(const std::string& script);
	
	void setDamage(int dmg);
	int getDamage() const;

	bool isActive() const;
	void MarkForDeletion();

	void Update();
	void Draw();
private:
	void _initLua();

public:
	
	LUA_FUNC s_Move(lua_State * l);
	LUA_FUNC s_setSize(lua_State * l);
	LUA_FUNC s_setColor(lua_State * l);
	LUA_FUNC s_getPosition(lua_State * l);
	LUA_FUNC s_isActive(lua_State * l);
	LUA_FUNC s_DisableAndDelete(lua_State * l);
	LUA_FUNC s_setDamage(lua_State * l);
	LUA_FUNC s_getDamage(lua_State * l);
	LUA_FUNC s_getDirection(lua_State * l);
}; 
