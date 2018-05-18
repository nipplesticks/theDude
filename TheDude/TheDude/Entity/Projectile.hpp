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

public:
	Projectile(float x, float y, float dx, float dy);
	~Projectile();
	void setScript(const std::string& script);
	
	bool canTravel() const;
	
	void setDamage(int dmg);
	int getDamage() const;

	void Update();
	void Draw();
private:
	void _initLua();

public:
	LUA_FUNC s_Move(lua_State * l);


}; 
