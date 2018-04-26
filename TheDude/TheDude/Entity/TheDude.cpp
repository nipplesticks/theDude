#include "TheDude.h"

std::string TheDude::meta = "TheDudeMeta";

TheDude::TheDude(sf::Vector2f position, sf::Color color, sf::Vector2f speed, float attackStart, float defenceStart) : Character(position, color, speed, attackStart, defenceStart)
{

}

TheDude::TheDude(float x, float y, sf::Color color, float speedX, float speedY, float attackStart, float defenceStart) : Character(x,y,color,speedX,speedY, attackStart, defenceStart)
{
}

TheDude::TheDude(float x, float y, sf::Color color, float speed, float attackStart, float defenceStart) : Character(x, y, color, speed, attackStart, defenceStart)
{
}

TheDude::TheDude() : Character()
{
}

TheDude::~TheDude()
{
}

void TheDude::update(float dt)
{
	Character::update(dt); 
}

int TheDude::s_getPosition(lua_State * l)
{
	TheDude* plr = OurLua::getInstanceOf<TheDude>(l, 1, meta);
	sf::Vector2f pos = plr->getPosition();
	std::vector<float> v;
	v.push_back(pos.x);
	v.push_back(pos.y);
	OurLua::setFloats(l, v);

	return static_cast<int>(v.size());
}

int TheDude::s_getSpeed(lua_State * l)
{
	TheDude* plr = OurLua::getInstanceOf<TheDude>(l, 1, meta);
	sf::Vector2f pos = plr->getSpeed();
	std::vector<float> v;
	v.push_back(pos.x);
	v.push_back(pos.y);
	OurLua::setFloats(l, v);

	return static_cast<int>(v.size());
}

int TheDude::s_isActive(lua_State * l)
{
	TheDude* plr = OurLua::getInstanceOf<TheDude>(l, 1, meta);
	bool a = plr->getIsActive();
	std::vector<bool> v;
	v.push_back(a);
	OurLua::setBooleans(l, v);

	return static_cast<int>(v.size());
}

#include <iostream>
int TheDude::s_setPosition(lua_State * l)
{
	TheDude* plr = OurLua::getInstanceOf<TheDude>(l, 1, meta);
	std::vector<float> pos = OurLua::getFloats(l, 2);
	plr->setPosition(pos[1], pos[0]);
	return 0;
}

int TheDude::s_setSpeed(lua_State * l)
{
	TheDude* plr = OurLua::getInstanceOf<TheDude>(l, 1, meta);
	std::vector<float> speed = OurLua::getFloats(l, 2);
	plr->setSpeed(speed[1], speed[0]);
	return 0;
}

int TheDude::s_setActiveness(lua_State * l)
{
	TheDude* plr = OurLua::getInstanceOf<TheDude>(l, 1, meta);
	std::vector<bool> b = OurLua::getBoolean(l, 1);
	plr->setIsActive(b[0]);
	return 0;
}

int TheDude::s_setColor(lua_State * l)
{
	TheDude* plr = OurLua::getInstanceOf<TheDude>(l, 1, meta);
	std::vector<int> color = OurLua::getIntegers(l, 3);
	sf::Color c = sf::Color(color[2], color[1], color[0]);
	plr->setColor(c);
	return 0;
}

int TheDude::s_move(lua_State * l)
{
	TheDude* plr = OurLua::getInstanceOf<TheDude>(l, 1, meta);
	std::vector<float> dir = OurLua::getFloats(l, 2);
	plr->move(dir[1], dir[0]);

	return 0;
}

int TheDude::s_draw(lua_State * l)
{
	TheDude* plr = OurLua::getInstanceOf<TheDude>(l, 1, meta);
	plr->draw();
	return 0;
}

int TheDude::s_getHealth(lua_State * l)
{
	TheDude* plr = OurLua::getInstanceOf<TheDude>(l, 1, meta);
	float h = plr->getHealth();
	std::vector<float> v;
	v.push_back(h);
	OurLua::setFloats(l, v);

	return static_cast<int>(v.size());
}

int TheDude::s_isAttacking(lua_State * l)
{
	TheDude* plr = OurLua::getInstanceOf<TheDude>(l, 1, meta);
	bool a = plr->getAttacking();
	std::vector<bool> v;
	v.push_back(a);
	OurLua::setBooleans(l, v);

	return static_cast<int>(v.size());
}

int TheDude::s_getAttackStats(lua_State * l)
{
	TheDude* plr = OurLua::getInstanceOf<TheDude>(l, 1, meta);
	float h = plr->getAttackStat();
	std::vector<float> v;
	v.push_back(h);
	OurLua::setFloats(l, v);

	return static_cast<int>(v.size());
}

int TheDude::s_getDefenceStat(lua_State * l)
{
	TheDude* plr = OurLua::getInstanceOf<TheDude>(l, 1, meta);
	float h = plr->getDefenceStat();
	std::vector<float> v;
	v.push_back(h);
	OurLua::setFloats(l, v);

	return static_cast<int>(v.size());
}

int TheDude::s_sethealth(lua_State * l)
{
	TheDude* plr = OurLua::getInstanceOf<TheDude>(l, 1, meta);
	std::vector<float> s = OurLua::getFloats(l, 1);
	plr->setHealth(s[0]);
	return 0;
}

int TheDude::s_setAttackingState(lua_State * l)
{
	TheDude* plr = OurLua::getInstanceOf<TheDude>(l, 1, meta);
	std::vector<bool> s = OurLua::getBoolean(l, 1);
	plr->setAttacking(s[0]);
	return 0;
}

int TheDude::s_setDamage(lua_State * l)
{
	TheDude* plr = OurLua::getInstanceOf<TheDude>(l, 1, meta);
	std::vector<float> s = OurLua::getFloats(l, 1);
	plr->setAttackStat(s[0]);
	return 0;
}

int TheDude::s_setDefence(lua_State * l)
{
	TheDude* plr = OurLua::getInstanceOf<TheDude>(l, 1, meta);
	std::vector<float> s = OurLua::getFloats(l, 1);
	plr->setDefenceStat(s[0]);
	return 0;
}

int TheDude::s_changeDamage(lua_State * l)
{
	TheDude* plr = OurLua::getInstanceOf<TheDude>(l, 1, meta);
	std::vector<float> s = OurLua::getFloats(l, 1);

	if (s[0] > 0)
		plr->increaseAttack(s[0]);
	else
		plr->decreaseAttack(s[0]);

	return 0;
}

int TheDude::s_changeDefence(lua_State * l)
{
	TheDude* plr = OurLua::getInstanceOf<TheDude>(l, 1, meta);
	std::vector<float> s = OurLua::getFloats(l, 1);

	if (s[0] > 0)
		plr->increaseDefence(s[0]);
	else
		plr->decreaseDefence(s[0]);

	return 0;
}

int TheDude::s_changeHP(lua_State * l)
{
	TheDude* plr = OurLua::getInstanceOf<TheDude>(l, 1, meta);
	std::vector<float> s = OurLua::getFloats(l, 1);

	if (s[0] > 0)
		plr->decreaseHP(-s[0]);
	else
		plr->decreaseHP(s[0]);

	return 0;
}

int TheDude::s_attack(lua_State * l)
{
	TheDude* plr = OurLua::getInstanceOf<TheDude>(l, 1, meta);
	plr->attack();
	return 0;
}

int TheDude::s_update(lua_State * l)
{
	TheDude* plr = OurLua::getInstanceOf<TheDude>(l, 1, meta);
	plr->update(1 / 60.0f);
	return 0;
}

int TheDude::s_CreateTheDude(lua_State * l)
{
	TheDude** e = OurLua::createInstanceOf<TheDude>(l, meta);
	*e = new TheDude;
	return 1;
}

int TheDude::s_DestroyTheDude(lua_State * l)
{
	TheDude* plr = OurLua::getInstanceOf<TheDude>(l, 1, meta);
	delete plr;
	return 0;
}
