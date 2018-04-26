#include "Enemy.hpp"

std::string Enemy::meta = "EnemyMeta";

Enemy::Enemy(sf::Vector2f position, sf::Color color, sf::Vector2f speed, float attackStart, float defenceStart) : Character(position, color, speed, attackStart, defenceStart)
{
}

Enemy::Enemy(float x, float y, sf::Color color, float speedX, float speedY, float attackStart, float defenceStart) : Character(x,y,color,speedX,speedY,attackStart,defenceStart)
{
}

Enemy::Enemy(float x, float y, sf::Color color, float speed, float attackStart, float defenceStart) : Character(x,y,color,speed,attackStart,defenceStart)
{
}
Enemy::Enemy() : Character()
{

}

Enemy::~Enemy()
{
}

void Enemy::update(float dt)
{
	Character::update(dt); 
}

int Enemy::s_getPosition(lua_State * l)
{
	Enemy* emy = OurLua::getInstanceOf<Enemy>(l, 1, meta);
	sf::Vector2f pos = emy->getPosition();
	std::vector<float> v;
	v.push_back(pos.x);
	v.push_back(pos.y);
	OurLua::setFloats(l, v);

	return static_cast<int>(v.size());
}

int Enemy::s_getSpeed(lua_State * l)
{
	Enemy* emy = OurLua::getInstanceOf<Enemy>(l, 1, meta);
	sf::Vector2f pos = emy->getSpeed();
	std::vector<float> v;
	v.push_back(pos.x);
	v.push_back(pos.y);
	OurLua::setFloats(l, v);

	return static_cast<int>(v.size());
}

int Enemy::s_isActive(lua_State * l)
{
	Enemy* emy = OurLua::getInstanceOf<Enemy>(l, 1, meta);
	bool a = emy->getIsActive();
	std::vector<bool> v;
	v.push_back(a);
	OurLua::setBooleans(l, v);

	return static_cast<int>(v.size());
}

#include <iostream>
int Enemy::s_setPosition(lua_State * l)
{
	Enemy* emy = OurLua::getInstanceOf<Enemy>(l, 1, meta);
	std::vector<float> pos = OurLua::getFloats(l, 2);
	emy->setPosition(pos[1], pos[0]);
	return 0;
}

int Enemy::s_setSpeed(lua_State * l)
{
	Enemy* emy = OurLua::getInstanceOf<Enemy>(l, 1, meta);
	std::vector<float> speed = OurLua::getFloats(l, 2);
	emy->setSpeed(speed[1], speed[0]);
	return 0;
}

int Enemy::s_setActiveness(lua_State * l)
{
	Enemy* emy = OurLua::getInstanceOf<Enemy>(l, 1, meta);
	std::vector<bool> b = OurLua::getBoolean(l, 1);
	emy->setIsActive(b[0]);
	return 0;
}

int Enemy::s_setColor(lua_State * l)
{
	Enemy* emy = OurLua::getInstanceOf<Enemy>(l, 1, meta);
	std::vector<int> color = OurLua::getIntegers(l, 3);
	sf::Color c = sf::Color(color[2], color[1], color[0]);
	emy->setColor(c);
	return 0;
}

int Enemy::s_move(lua_State * l)
{
	Enemy* emy = OurLua::getInstanceOf<Enemy>(l, 1, meta);
	std::vector<float> dir = OurLua::getFloats(l, 2);
	emy->move(dir[1], dir[0]);

	return 0;
}

int Enemy::s_draw(lua_State * l)
{
	Enemy* emy = OurLua::getInstanceOf<Enemy>(l, 1, meta);
	emy->draw();
	return 0;
}

int Enemy::s_getHealth(lua_State * l)
{
	Enemy* emy = OurLua::getInstanceOf<Enemy>(l, 1, meta);
	float h = emy->getHealth();
	std::vector<float> v;
	v.push_back(h);
	OurLua::setFloats(l, v);

	return static_cast<int>(v.size());
}

int Enemy::s_isAttacking(lua_State * l)
{
	Enemy* emy = OurLua::getInstanceOf<Enemy>(l, 1, meta);
	bool a = emy->getAttacking();
	std::vector<bool> v;
	v.push_back(a);
	OurLua::setBooleans(l, v);

	return static_cast<int>(v.size());
}

int Enemy::s_getAttackStats(lua_State * l)
{
	Enemy* emy = OurLua::getInstanceOf<Enemy>(l, 1, meta);
	float h = emy->getAttackStat();
	std::vector<float> v;
	v.push_back(h);
	OurLua::setFloats(l, v);

	return static_cast<int>(v.size());
}

int Enemy::s_getDefenceStat(lua_State * l)
{
	Enemy* emy = OurLua::getInstanceOf<Enemy>(l, 1, meta);
	float h = emy->getDefenceStat();
	std::vector<float> v;
	v.push_back(h);
	OurLua::setFloats(l, v);

	return static_cast<int>(v.size());
}

int Enemy::s_sethealth(lua_State * l)
{
	Enemy* emy = OurLua::getInstanceOf<Enemy>(l, 1, meta);
	std::vector<float> s = OurLua::getFloats(l, 1);
	emy->setHealth(s[0]);
	return 0;
}

int Enemy::s_setAttackingState(lua_State * l)
{
	Enemy* emy = OurLua::getInstanceOf<Enemy>(l, 1, meta);
	std::vector<bool> s = OurLua::getBoolean(l, 1);
	emy->setAttacking(s[0]);
	return 0;
}

int Enemy::s_setDamage(lua_State * l)
{
	Enemy* emy = OurLua::getInstanceOf<Enemy>(l, 1, meta);
	std::vector<float> s = OurLua::getFloats(l, 1);
	emy->setAttackStat(s[0]);
	return 0;
}

int Enemy::s_setDefence(lua_State * l)
{
	Enemy* emy = OurLua::getInstanceOf<Enemy>(l, 1, meta);
	std::vector<float> s = OurLua::getFloats(l, 1);
	emy->setDefenceStat(s[0]);
	return 0;
}

int Enemy::s_changeDamage(lua_State * l)
{
	Enemy* emy = OurLua::getInstanceOf<Enemy>(l, 1, meta);
	std::vector<float> s = OurLua::getFloats(l, 1);
	
	if (s[0] > 0)
		emy->increaseAttack(s[0]);
	else
		emy->decreaseAttack(s[0]);

	return 0;
}

int Enemy::s_changeDefence(lua_State * l)
{
	Enemy* emy = OurLua::getInstanceOf<Enemy>(l, 1, meta);
	std::vector<float> s = OurLua::getFloats(l, 1);

	if (s[0] > 0)
		emy->increaseDefence(s[0]);
	else
		emy->decreaseDefence(s[0]);

	return 0;
}

int Enemy::s_changeHP(lua_State * l)
{
	Enemy* emy = OurLua::getInstanceOf<Enemy>(l, 1, meta);
	std::vector<float> s = OurLua::getFloats(l, 1);

	if (s[0] > 0)
		emy->decreaseHP(-s[0]);
	else
		emy->decreaseHP(s[0]);

	return 0;
}

int Enemy::s_attack(lua_State * l)
{
	Enemy* emy = OurLua::getInstanceOf<Enemy>(l, 1, meta);
	emy->attack();
	return 0;
}

int Enemy::s_update(lua_State * l)
{
	Enemy* emy = OurLua::getInstanceOf<Enemy>(l, 1, meta);
	emy->update(1/60.0f);
	return 0;
}

int Enemy::s_CreateEnemy(lua_State * l)
{
	Enemy** e = OurLua::createInstanceOf<Enemy>(l, meta);
	*e = new Enemy;
	return 1;
}

int Enemy::s_DestroyEnemy(lua_State * l)
{
	Enemy* emy = OurLua::getInstanceOf<Enemy>(l, 1, meta);
	delete emy;
	return 0;
}
