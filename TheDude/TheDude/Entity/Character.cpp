#include "Character.hpp"

std::string Character::metaTable = "Character";
sf::Vector2f Character::playerPos = sf::Vector2f(0.0f, 0.0f);

Character::Character() : Entity()
{
	m_health = 100;
	m_maxHealth = 100;
	m_attack = 10;
	m_defence = 10;
	m_script = nullptr;
	m_HPBar.setFillColor(sf::Color::Green);
	m_HPBack.setFillColor(sf::Color::Red);
	setHPBarSize(50, -2, 50, 10);
}

Character::~Character()
{
	if (m_script)
		delete m_script;
}

void Character::setHPBarSize(int x, int y, int sx, int sy)
{
	m_HPOffset.x = x;
	m_HPOffset.y = y;
	m_HPScl.x = sx;
	m_HPScl.y = sy;
	
	sf::Vector2f rP = getShape().getPosition();
	sf::Vector2f rS = getShape().getSize();

	m_HPBar.setPosition(rP.x + rS.x * m_HPOffset.x * 0.01f, rP.y + rS.y * m_HPOffset.y * 0.01f);
	m_HPBar.setSize(sf::Vector2f(rS.x * m_HPScl.x * 0.01f, rS.y * m_HPScl.y * 0.01f));
	m_HPBar.setOrigin(m_HPBar.getSize() * 0.5f);

	m_HPBack.setPosition(m_HPBar.getPosition());
	m_HPBack.setSize(m_HPBar.getSize());
	m_HPBack.setOrigin(m_HPBar.getOrigin());
}

void Character::AddScript(const std::string & path)
{
	if (m_script)
		delete m_script;
	m_script = new OurLua(path);
	_initLua();
}

void Character::setSize(float x, float y)
{
	Entity::setSize(x, y);
	setHPBarSize(m_HPOffset.x, m_HPOffset.y, m_HPScl.x, m_HPScl.y);
}

bool Character::isDead() const
{
	return m_health <= 0;
}

void Character::setHealth(int health)
{
	m_health = health;
	m_maxHealth = health;
	sf::Vector2f rS = getShape().getSize();
	m_HPBar.setSize(sf::Vector2f(rS.x * m_HPScl.x * 0.01f, rS.y * m_HPScl.y * 0.01f));
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
	if (m_health < 0) m_health = 0;
	else if (m_health > m_maxHealth) m_health = m_maxHealth;
	float i = static_cast<float>(m_health) / m_maxHealth;
	sf::Vector2f rS = getShape().getSize();
	m_HPBar.setSize(sf::Vector2f(rS.x * m_HPScl.x * 0.01f * i, rS.y * m_HPScl.y * 0.01f));
}

int Character::getHealth() const
{
	return m_health;
}

int Character::getAttack() const
{
	return m_attack;
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

void Character::setViewPos(sf::Vector2f viewPos)
{
	Entity::setViewPos(viewPos);
	sf::Vector2f rP = getShape().getPosition();
	sf::Vector2f rS = getShape().getSize();
	m_HPBar.setPosition(rP.x + rS.x * m_HPOffset.x * 0.01f, rP.y + rS.y * m_HPOffset.y * 0.01f);
	m_HPBack.setPosition(m_HPBar.getPosition());
}

void Character::DrawOther(sf::RenderWindow * wnd)
{
	wnd->draw(m_HPBack);
	wnd->draw(m_HPBar);
}

#include "../States/Game.hpp"
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
	m_script->PushClassFunction(this, Character::s_SetSprite, "setSprite");
	m_script->PushClassFunction(this, Character::s_getDistanceToPlayer, "getDistanceToPlayer");
	m_script->PushClassFunction(this, Character::s_SetHPBar, "setHPBar");
	m_script->PushFunction(s_getPlayerPos, "getPlayerPosition");
	
	m_script->PushFunction(Game::s_isKeyPressed, "isKeyPressed");

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

int Character::s_SetSprite(lua_State * l)
{

	Character* c = OurLua::getInstanceOf<Character>(l, 1, metaTable);

	if (c)
	{
		std::vector<std::string> path = OurLua::getStrings(l, 1);
		c->setSprite(path[0]);
	}
	else
	{
		c = OurLua::getClassPointer<Character>(l);
		if (c)
		{
			std::vector<std::string> path = OurLua::getStrings(l, 1);
			c->setSprite(path[0]);
		}
	}

	return 0;
}

int Character::s_SetHPBar(lua_State * l)
{
	Character* c = OurLua::getInstanceOf<Character>(l, 1, metaTable);

	if (c)
	{
		std::vector<int> values = OurLua::getIntegers(l, 4);
		c->setHPBarSize(values[3], values[2], values[1], values[0]);
	}
	else
	{
		c = OurLua::getClassPointer<Character>(l);
		if (c)
		{
			std::vector<int> values = OurLua::getIntegers(l, 4);
			c->setHPBarSize(values[3], values[2], values[1], values[0]);
		}
	}

	return 0;
}

int Character::s_getDistanceToPlayer(lua_State * l)
{
	Character* c = OurLua::getInstanceOf<Character>(l, 1, metaTable);
	float dist = 9999999.0f;
	if (c)
	{
		sf::Vector2f ePos = c->getPosition();
		sf::Vector2f toPlayer = ePos - Character::playerPos;
		dist = sqrt(toPlayer.x * toPlayer.x + toPlayer.y * toPlayer.y);
	}
	else
	{
		c = OurLua::getClassPointer<Character>(l);
		if (c)
		{
			sf::Vector2f ePos = c->getPosition();
			sf::Vector2f toPlayer = ePos - Character::playerPos;
			dist = sqrt(toPlayer.x * toPlayer.x + toPlayer.y * toPlayer.y);
		}
	}
	std::vector<float> d;
	d.push_back(dist);
	OurLua::setFloats(l, d);
	return 1;
}

int Character::s_getPlayerPos(lua_State * l)
{
	std::vector<float> position;
	position.push_back(Character::playerPos.x);
	position.push_back(Character::playerPos.y);
	OurLua::setFloats(l, position);
	return 2;
}

