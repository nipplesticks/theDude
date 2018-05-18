#pragma once
#include "Entity.hpp"
#include "../OurLua/OurLua.hpp"
class Character : public Entity
{
public:
	static std::string metaTable;
	static sf::Vector2f playerPos;
private:
	int m_health; 
	int m_maxHealth;
	int m_attack; 
	int m_defence; 
	OurLua * m_script;
	
	sf::RectangleShape	m_HPBar;
	sf::RectangleShape	m_HPBack;
	sf::Vector2f		m_HPOffset;
	sf::Vector2f		m_HPScl;

	sf::Vector2f		m_moveReq;


public:
	Character();
	~Character(); 

	// Put size to -1 if you want to stretch to spr size
	void setHPBarSize(int x = 50, int y = 100, int sx = 100, int sy = 10);

	void AddScript(const std::string &path);

	void setSize(float x, float y);

	bool isDead() const;
	void setHealth(int health); 
	void setAttack(int attack); 
	void setDefence(int defence); 
	
	void MoveRequest(float x, float y);

	//This will reset the moveRequest
	sf::Vector2f getMoveRequest();


	void AlterHealth(int health); 

	int getHealth() const; 
	int getAttack() const; 
	int getDefence() const; 

	void Update() override;
	void setViewPos(sf::Vector2f viewPos) override;
	void DrawOther(sf::RenderWindow * wnd);
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
	LUA_FUNC s_SetHPBar(lua_State* l);
	LUA_FUNC s_getDistanceToPlayer(lua_State * l);
	LUA_FUNC s_getPlayerPos(lua_State * l);
	LUA_FUNC s_MoveRequest(lua_State * l);
	LUA_FUNC s_getMoveRequest(lua_State * l);
};
