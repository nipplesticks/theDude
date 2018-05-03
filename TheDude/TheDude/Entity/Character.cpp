#include "Character.hpp"

std::string Character::metaTable = "Character";

Character::Character() : Entity()
{
	m_health = 100;
	m_attack = 10;
	m_defence = 10;
	m_script = nullptr;
}

Character::~Character()
{
	if (m_script)
		delete m_script;
}

void Character::AddScript(const std::string & path)
{
	if (m_script)
		delete m_script;
	m_script = new OurLua(path);
	_initLua();
}

bool Character::isDead() const
{
	return m_health <= 0;
}

void Character::setHealth(int health)
{
	m_health = health;
}

void Character::setAttack(int attack)
{
	m_attack = attack;
}

void Character::setDefence(int defence)
{
	m_defence = defence;
}

void Character::AlterHealth(int health)
{
	m_health += health;
}

int Character::getHealth() const
{
	return m_health;
}

int Character::getAttack() const
{
	return m_health;
}

int Character::getDefence() const
{
	return m_health;
}

void Character::Update()
{
	if (m_script)
		m_script->Update();
}

void Character::_initLua()
{
	m_script->PushClassFunction(this, Character::s_setColor, "setColor");
	m_script->PushClassFunction(this, Character::s_setPosition, "setPosition");
	m_script->PushClassFunction(this, Character::s_Move, "Move");
	m_script->PushClassFunction(this, Character::s_setSize, "setSize");
	m_script->PushClassFunction(this, Character::s_setOrigin, "setOrigin");
	m_script->PushClassFunction(this, Character::s_getPosition, "getPosition");
	m_script->PushClassFunction(this, Character::s_getSize, "getSize");
	m_script->PushClassFunction(this, Character::s_getColor, "getColor");
	//m_script->PushClassFunction(this, Character::s_Draw, "Draw");
	//m_script->PushClassFunction(this, Character::s_AddScript, "AddScript");
	m_script->PushClassFunction(this, Character::s_isDead, "isDead");
	m_script->PushClassFunction(this, Character::s_setHealth, "setHealth");
	m_script->PushClassFunction(this, Character::s_setAttack, "setAttack");
	m_script->PushClassFunction(this, Character::s_setDefence, "setDefence");
	m_script->PushClassFunction(this, Character::s_AlterHealth, "AlterHealth");
	m_script->PushClassFunction(this, Character::s_getHealth, "getHealth");
	m_script->PushClassFunction(this, Character::s_getAttack, "getAttack");
	m_script->PushClassFunction(this, Character::s_getDefence, "getDefence");
	m_script->InitLua();
	//m_script->PushClassFunction(this, Character::s_Update, "Update");
}

int Character::s_setColor(lua_State * l)
{
	Character* c = OurLua::getInstanceOf<Character>(l, 1, metaTable);
	
	if (c)
	{
		std::vector<int> color = OurLua::getIntegers(l, 3);
		c->setColor(color[2], color[1], color[0]);
	}
	else
	{
		c = OurLua::getClassPointer<Character>(l);
		if (c)
		{
			std::vector<int> color = OurLua::getIntegers(l, 3);
			c->setColor(color[2], color[1], color[0]);
		}
	}

	return 0;
}
int Character::s_setPosition(lua_State * l)
{
	Character* c = OurLua::getInstanceOf<Character>(l, 1, metaTable);
	
	if (c)
	{
		std::vector<int> position = OurLua::getIntegers(l, 2);
		c->setPosition(position[1], position[0]);
	}
	else
	{
		c = OurLua::getClassPointer<Character>(l);
		if (c)
		{
			std::vector<int> position = OurLua::getIntegers(l, 2);
			c->setPosition(position[1], position[0]);
		}
	}

	return 0;
}
int Character::s_Move(lua_State * l)
{
	Character* c = OurLua::getInstanceOf<Character>(l, 1, metaTable);

	if (c)
	{
		std::vector<float> position = OurLua::getFloats(l, 2);
		c->Move(position[1], position[0]);
	}
	else
	{
		c = OurLua::getClassPointer<Character>(l);
		if (c)
		{
			std::vector<float> position = OurLua::getFloats(l, 2);
			c->Move(position[1], position[0]);
		}
	}


	return 0;
}
int Character::s_setSize(lua_State * l)
{
	Character* c = OurLua::getInstanceOf<Character>(l, 1, metaTable);

	if (c)
	{
		std::vector<float> size = OurLua::getFloats(l, 2);
		c->setSize(size[1], size[0]);
	}
	else
	{
		c = OurLua::getClassPointer<Character>(l);
		if (c)
		{
			std::vector<float> size = OurLua::getFloats(l, 2);
			c->setSize(size[1], size[0]);
		}
	}
	return 0;
}
int Character::s_setOrigin(lua_State * l)
{
	Character* c = OurLua::getInstanceOf<Character>(l, 1, metaTable);

	if (c)
	{
		std::vector<float> origin = OurLua::getFloats(l, 2);
		c->setOrigin(origin[1], origin[0]);
	}
	else
	{
		c = OurLua::getClassPointer<Character>(l);
		if (c)
		{
			std::vector<float> origin = OurLua::getFloats(l, 2);
			c->setOrigin(origin[1], origin[0]);
		}
	}
	return 0;
}
int Character::s_getPosition(lua_State * l)
{
	Character* c = OurLua::getInstanceOf<Character>(l, 1, metaTable);
	std::vector<float> position;
	if (c)
	{
		sf::Vector2f pos = c->getPosition();
		position.push_back(pos.x);
		position.push_back(pos.y);
		OurLua::setFloats(l, position);
	}
	else
	{
		c = OurLua::getClassPointer<Character>(l);
		if (c)
		{
			sf::Vector2f pos = c->getPosition();
			position.push_back(pos.x);
			position.push_back(pos.y);
			OurLua::setFloats(l, position);
		}
	}
	return static_cast<int>(position.size());
}
int Character::s_getSize(lua_State * l)
{
	Character* c = OurLua::getInstanceOf<Character>(l, 1, metaTable);
	std::vector<float> size;
	if (c)
	{
		sf::Vector2f temp = c->getSize();
		size.push_back(temp.x);
		size.push_back(temp.y);
		OurLua::setFloats(l, size);
	}
	else
	{
		c = OurLua::getClassPointer<Character>(l);
		if (c)
		{
			sf::Vector2f temp = c->getSize();
			size.push_back(temp.x);
			size.push_back(temp.y);
			OurLua::setFloats(l, size);
		}
	}
	return static_cast<int>(size.size());
}
int Character::s_getColor(lua_State * l)
{
	Character* c = OurLua::getInstanceOf<Character>(l, 1, metaTable);
	std::vector<int> color;
	if (c)
	{
		sf::Color temp = c->getColor();
		color.push_back(temp.r);
		color.push_back(temp.g);
		color.push_back(temp.b);
		OurLua::setIntegers(l, color);
	}
	else
	{
		c = OurLua::getClassPointer<Character>(l);
		if (c)
		{
			sf::Color temp = c->getColor();
			color.push_back(temp.r);
			color.push_back(temp.g);
			color.push_back(temp.b);
			OurLua::setIntegers(l, color);
		}
	}
	return static_cast<int>(color.size());
}
int Character::s_Draw(lua_State * l)
{
	Character* c = OurLua::getInstanceOf<Character>(l, 1, metaTable);
	if (c)
	{
		c->Draw();
	}

	return 0;
}
int Character::s_AddScript(lua_State * l)
{
	Character* c = OurLua::getInstanceOf<Character>(l, 1, metaTable);

	if (c)
	{
		std::vector<std::string> path = OurLua::getStrings(l, 1);
		c->AddScript(path[0]);
	}

	return 0;
}
int Character::s_isDead(lua_State * l)
{
	Character* c = OurLua::getInstanceOf<Character>(l, 1, metaTable);
	std::vector<bool> dead;
	if (c)
	{
		dead.push_back(c->isDead());

		OurLua::setBooleans(l, dead);
	}
	else
	{
		c = OurLua::getClassPointer<Character>(l);
		if (c)
		{
			dead.push_back(c->isDead());

			OurLua::setBooleans(l, dead);
		}
	}
	return static_cast<int>(dead.size());
}
int Character::s_setHealth(lua_State * l)
{
	Character* c = OurLua::getInstanceOf<Character>(l, 1, metaTable);

	if (c)
	{
		std::vector<int> health = OurLua::getIntegers(l, 1);
		c->setHealth(health[0]);
	}
	else
	{
		c = OurLua::getClassPointer<Character>(l);
		if (c)
		{
			std::vector<int> health = OurLua::getIntegers(l, 1);
			c->setHealth(health[0]);
		}
	}
	return 0;
}
int Character::s_setAttack(lua_State * l)
{
	Character* c = OurLua::getInstanceOf<Character>(l, 1, metaTable);

	if (c)
	{
		std::vector<int> attack = OurLua::getIntegers(l, 1);
		c->setAttack(attack[0]);
	}
	else
	{
		c = OurLua::getClassPointer<Character>(l);
		if (c)
		{
			std::vector<int> attack = OurLua::getIntegers(l, 1);
			c->setAttack(attack[0]);
		}
	}
	return 0;
}
int Character::s_setDefence(lua_State * l)
{
	Character* c = OurLua::getInstanceOf<Character>(l, 1, metaTable);

	if (c)
	{
		std::vector<int> defence = OurLua::getIntegers(l, 1);
		c->setDefence(defence[0]);
	}
	else
	{
		c = OurLua::getClassPointer<Character>(l);
		if (c)
		{
			std::vector<int> defence = OurLua::getIntegers(l, 1);
			c->setDefence(defence[0]);
		}
	}
	return 0;
}
int Character::s_AlterHealth(lua_State * l)
{
	Character* c = OurLua::getInstanceOf<Character>(l, 1, metaTable);

	if (c)
	{
		std::vector<int> hp = OurLua::getIntegers(l, 1);
		c->AlterHealth(hp[0]);
	}
	else
	{
		c = OurLua::getClassPointer<Character>(l);
		if (c)
		{
			std::vector<int> hp = OurLua::getIntegers(l, 1);
			c->AlterHealth(hp[0]);
		}
	}
	return 0;
}
int Character::s_getHealth(lua_State * l)
{
	Character* c = OurLua::getInstanceOf<Character>(l, 1, metaTable);
	std::vector<int> hp;
	if (c)
	{
		hp.push_back(c->getHealth());

		OurLua::setIntegers(l, hp);
	}
	else
	{
		c = OurLua::getClassPointer<Character>(l);
		if (c)
		{
			hp.push_back(c->getHealth());

			OurLua::setIntegers(l, hp);
		}
	}
	return static_cast<int>(hp.size());
}
int Character::s_getAttack(lua_State * l)
{
	Character* c = OurLua::getInstanceOf<Character>(l, 1, metaTable);
	std::vector<int> a;
	if (c)
	{
		a.push_back(c->getAttack());

		OurLua::setIntegers(l, a);
	}
	else
	{
		c = OurLua::getClassPointer<Character>(l);
		if (c)
		{
			a.push_back(c->getAttack());

			OurLua::setIntegers(l, a);
		}
	}
	return static_cast<int>(a.size());
}
int Character::s_getDefence(lua_State * l)
{
	Character* c = OurLua::getInstanceOf<Character>(l, 1, metaTable);
	std::vector<int> d;
	if (c)
	{
		d.push_back(c->getDefence());

		OurLua::setIntegers(l, d);
	}
	else
	{
		c = OurLua::getClassPointer<Character>(l);
		if (c)
		{
			d.push_back(c->getDefence());

			OurLua::setIntegers(l, d);
		}
	}
	return static_cast<int>(d.size());
}
int Character::s_Update(lua_State * l)
{
	Character* c = OurLua::getInstanceOf<Character>(l, 1, metaTable);
	if (c)
	{
		c->Update();
	}

	return 0;
}
int Character::s_Create(lua_State * l)
{
	Character ** c = OurLua::createInstanceOf<Character>(l, metaTable);
	*c = new Character;
	return 1;
}
int Character::s_Destroy(lua_State * l)
{
	Character* c = OurLua::getInstanceOf<Character>(l, 1, metaTable);
	if (c)
	{
		delete c;
	}

	return 0;
}

