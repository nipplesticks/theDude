#include "Weapon.hpp"

std::string Weapon::metaTable = "Weapon";

Weapon::Weapon(const std::string & script)
{
	m_scriptPath = script;
}

Weapon::~Weapon()
{
	for (auto & b : bulletContainer)
		delete b;
}

void Weapon::Shoot(float x, float y, float dx, float dy)
{
	Projectile* p = new Projectile(x, y, dx, dy);
	p->setScript(m_scriptPath);
	bulletContainer.push_back(p);
}

void Weapon::Update()
{
	for (auto & b : bulletContainer)
		b->Update();
}

void Weapon::Draw(sf::RenderWindow * wnd, sf::Vector2f camPos)
{
	for (auto & lol : bulletContainer)
	{
		lol->setViewPos(lol->getPosition() - camPos);
		wnd->draw(lol->getShape());
	}
}

int Weapon::s_Create(lua_State * l)
{
	std::string path = OurLua::getStrings(l, 1)[0];
	Weapon ** w = OurLua::createInstanceOf<Weapon>(l, metaTable);
	*w = new Weapon(path);
	return 1;
}

int Weapon::s_Destroy(lua_State * l)
{
	Weapon* c = OurLua::getInstanceOf<Weapon>(l, 1, metaTable);
	if (c)
	{
		delete c;
	}

	return 0;
}

int Weapon::s_Shoot(lua_State * l)
{
	Weapon* w = OurLua::getInstanceOf<Weapon>(l, 1, metaTable);

	if (w)
	{
		std::vector<float> s = OurLua::getFloats(l, 4);
		w->Shoot(s[3], s[2], s[1], s[0]);
	}
	else
	{
		w = OurLua::getClassPointer<Weapon>(l);
		if (w)
		{
			std::vector<float> s = OurLua::getFloats(l, 4);
			w->Shoot(s[3], s[2], s[1], s[0]);
		}
	}

	return 0;
}
