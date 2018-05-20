#include "Projectile.hpp"

std::string Projectile::metaTable = "Projectile";
Projectile::Projectile(float x, float y, float dx, float dy)
{
	m_script = nullptr;
	Entity::setPosition(x, y);

	//TEMP
	Entity::setSize(2, 2);
	Entity::setColor(255, 0, 0);
	//END

	m_active = true;

	m_dir.x = dx;
	m_dir.y = dy;
	m_damage = 0;
}

Projectile::~Projectile()
{
	delete m_script;
}

void Projectile::setScript(const std::string & script)
{
	if (m_script)
		delete m_script;
	m_script = new OurLua(script);
	_initLua();
}

void Projectile::setDamage(int dmg)
{
	m_damage = dmg;
}

int Projectile::getDamage() const
{
	return m_damage;
}

bool Projectile::isActive() const
{
	return m_active;
}

void Projectile::MarkForDeletion()
{
	m_active = false;
}

void Projectile::Update()
{
	m_script->Update();
}

void Projectile::Draw()
{
	Entity::Draw();
}

void Projectile::_initLua()
{
	// Push Class Functions
	m_script->PushClassFunction(this, Projectile::s_Move, "Move");
	m_script->PushClassFunction(this, Projectile::s_setSize, "setSize");
	m_script->PushClassFunction(this, Projectile::s_setColor, "setColor");
	m_script->PushClassFunction(this, Projectile::s_getPosition, "getPosition");
	m_script->PushClassFunction(this, Projectile::s_isActive, "isActive");
	m_script->PushClassFunction(this, Projectile::s_setDamage, "setDamage");
	m_script->PushClassFunction(this, Projectile::s_getDamage, "getDamage");
	m_script->PushClassFunction(this, Projectile::s_getDirection, "getDirection");
	m_script->PushClassFunction(this, Projectile::s_DisableAndDelete, "Disable");

	m_script->InitLua();
}

int Projectile::s_Move(lua_State * l)
{
	Projectile* c = OurLua::getInstanceOf<Projectile>(l, 1, metaTable);

	if (c)
	{
		std::vector<float> position = OurLua::getFloats(l, 2);
		c->Move(position[1], position[0]);
	}
	else
	{
		c = OurLua::getClassPointer<Projectile>(l);
		if (c)
		{
			std::vector<float> position = OurLua::getFloats(l, 2);
			c->Move(position[1], position[0]);
		}
	}
	return 0;
}

int Projectile::s_setSize(lua_State * l)
{
	Projectile* c = OurLua::getInstanceOf<Projectile>(l, 1, metaTable);

	if (c)
	{
		std::vector<float> size = OurLua::getFloats(l, 2);
		c->setSize(size[1], size[0]);
	}
	else
	{
		c = OurLua::getClassPointer<Projectile>(l);
		if (c)
		{
			std::vector<float> size = OurLua::getFloats(l, 2);
			c->setSize(size[1], size[0]);
		}
	}
	return 0;
}

int Projectile::s_setColor(lua_State * l)
{
	Projectile* c = OurLua::getInstanceOf<Projectile>(l, 1, metaTable);

	if (c)
	{
		std::vector<int> color = OurLua::getIntegers(l, 3);
		c->setColor(color[2], color[1], color[0]);
	}
	else
	{
		c = OurLua::getClassPointer<Projectile>(l);
		if (c)
		{
			std::vector<int> color = OurLua::getIntegers(l, 3);
			c->setColor(color[2], color[1], color[0]);
		}
	}

	return 0;
}

int Projectile::s_getPosition(lua_State * l)
{
	Projectile* c = OurLua::getInstanceOf<Projectile>(l, 1, metaTable);
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
		c = OurLua::getClassPointer<Projectile>(l);
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

int Projectile::s_isActive(lua_State * l)
{
	Projectile* c = OurLua::getInstanceOf<Projectile>(l, 1, metaTable);
	std::vector<bool> dead;
	if (c)
	{
		dead.push_back(c->isActive());

		OurLua::setBooleans(l, dead);
	}
	else
	{
		c = OurLua::getClassPointer<Projectile>(l);
		if (c)
		{
			dead.push_back(c->isActive());

			OurLua::setBooleans(l, dead);
		}
	}
	return static_cast<int>(dead.size());
}

int Projectile::s_DisableAndDelete(lua_State * l)
{
	Projectile* c = OurLua::getInstanceOf<Projectile>(l, 1, metaTable);
	std::vector<int> a;
	if (c)
	{
		c->MarkForDeletion();
	}
	else
	{
		c = OurLua::getClassPointer<Projectile>(l);
		if (c)
		{
			c->MarkForDeletion();
		}
	}
	return 0;
}

int Projectile::s_setDamage(lua_State * l)
{
	Projectile* c = OurLua::getInstanceOf<Projectile>(l, 1, metaTable);

	if (c)
	{
		std::vector<int> attack = OurLua::getIntegers(l, 1);
		c->setDamage(attack[0]);
	}
	else
	{
		c = OurLua::getClassPointer<Projectile>(l);
		if (c)
		{
			std::vector<int> attack = OurLua::getIntegers(l, 1);
			c->setDamage(attack[0]);
		}
	}
	return 0;
}

int Projectile::s_getDamage(lua_State * l)
{
	Projectile* c = OurLua::getInstanceOf<Projectile>(l, 1, metaTable);
	std::vector<int> a;
	if (c)
	{
		a.push_back(c->getDamage());

		OurLua::setIntegers(l, a);
	}
	else
	{
		c = OurLua::getClassPointer<Projectile>(l);
		if (c)
		{
			a.push_back(c->getDamage());

			OurLua::setIntegers(l, a);
		}
	}
	return static_cast<int>(a.size());
}

int Projectile::s_getDirection(lua_State * l)
{
	Projectile* c = OurLua::getInstanceOf<Projectile>(l, 1, metaTable);
	if (c)
	{
		sf::Vector2f dir = c->m_dir;

		float denum = sqrt(dir.x * dir.x + dir.y * dir.y);
		if (denum != 0)
			dir = dir / denum;

		std::vector<float> values;
		values.push_back(dir.x);
		values.push_back(dir.y);
		OurLua::setFloats(l, values);
	}
	else
	{
		c = OurLua::getClassPointer<Projectile>(l);
		if (c)
		{
			sf::Vector2f dir = c->m_dir;

			float denum = sqrt(dir.x * dir.x + dir.y * dir.y);
			if (denum != 0)
				dir = dir / denum;

			std::vector<float> values;
			values.push_back(dir.x);
			values.push_back(dir.y);
			OurLua::setFloats(l, values);
		}
	}
	return 2;
}
