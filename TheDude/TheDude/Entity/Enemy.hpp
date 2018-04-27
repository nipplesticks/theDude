#pragma once
#include "Character.hpp"
#include "../Scripts/OurLua.h"
class Enemy : public Character
{
public:
	static std::string meta;
	Enemy(sf::Vector2f position, sf::Color color, sf::Vector2f speed, float attackStart, float defenceStart);
	Enemy(float x, float y, sf::Color color, float speedX, float speedY, float attackStart, float defenceStart); 
	Enemy(float x, float y, sf::Color color, float speed, float attackStart, float defenceStart); 
	Enemy();

	~Enemy(); 

	void update(float dt) override; 

public:			//Lua stuff
	// Entity stuff
	static int s_getPosition(lua_State * l);
	static int s_getSpeed(lua_State * l);
	static int s_isActive(lua_State * l);
	static int s_setPosition(lua_State * l);
	static int s_setSpeed(lua_State * l);
	static int s_setActiveness(lua_State * l);
	static int s_setColor(lua_State * l);
	static int s_move(lua_State * l);
	static int s_draw(lua_State * l);

	// Character stuff
	static int s_getHealth(lua_State * l);
	static int s_isAttacking(lua_State * l);
	static int s_getAttackStats(lua_State * l);
	static int s_getDefenceStat(lua_State * l);
	static int s_sethealth(lua_State * l);
	static int s_setAttackingState(lua_State * l);
	static int s_setDamage(lua_State * l);
	static int s_setDefence(lua_State * l);
	static int s_changeDamage(lua_State * l);
	static int s_changeDefence(lua_State * l);
	static int s_changeHP(lua_State * l);
	static int s_attack(lua_State * l);
	static int s_update(lua_State * l);

	// Enemy Stuff
	static int s_CreateEnemy(lua_State * l);
	static int s_DestroyEnemy(lua_State * l);

};
