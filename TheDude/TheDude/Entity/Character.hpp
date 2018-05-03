#pragma once
#include "Entity.hpp"
#include "../OurLua/OurLua.hpp"
class Character : public Entity
{
public:
	static std::string metaTable;

private:
	int m_health; 
	int m_attack; 
	int m_defence; 
	OurLua * m_script;

public:
	Character();
	~Character(); 

	void AddScript(const std::string &path);

	bool isDead() const;
	void setHealth(int health); 
	void setAttack(int attack); 
	void setDefence(int defence); 
	
	void AlterHealth(int health); 

	int getHealth() const; 
	int getAttack() const; 
	int getDefence() const; 

	void Update() override;

private:
	// Helpt Funcitons
	void _initLua();


public:

	// Lua funcitons
	LUA_FUNC s_setColor(lua_State * l);
	LUA_FUNC s_setPosition(lua_State * l);
	LUA_FUNC s_Move(lua_State * l);
	LUA_FUNC s_setSize(lua_State * l);
	LUA_FUNC s_setOrigin(lua_State * l);
	LUA_FUNC s_getPosition(lua_State * l);
	LUA_FUNC s_getSize(lua_State * l);
	LUA_FUNC s_getColor(lua_State * l);
	LUA_FUNC s_Draw(lua_State * l);
	LUA_FUNC s_AddScript(lua_State * l);
	LUA_FUNC s_isDead(lua_State * l);
	LUA_FUNC s_setHealth(lua_State * l);
	LUA_FUNC s_setAttack(lua_State * l);
	LUA_FUNC s_setDefence(lua_State * l);
	LUA_FUNC s_AlterHealth(lua_State * l);
	LUA_FUNC s_getHealth(lua_State * l);
	LUA_FUNC s_getAttack(lua_State * l);
	LUA_FUNC s_getDefence(lua_State * l);
	LUA_FUNC s_Update(lua_State * l);
	LUA_FUNC s_Create(lua_State * l);
	LUA_FUNC s_Destroy(lua_State * l);
	LUA_FUNC s_SetSprite(lua_State* l);
};
