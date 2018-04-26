#include "Scripts/OurLua.h"
#include <iostream>
#include <vector>
#include <string>

class e
{
private:
	std::string name;
	float p;
	float hp;

public:
	e(float p = 0, float hp = 100) : p(p), hp(hp) {}
	~e();

	void setName(std::string name) { this->name = name; }
	void setPos(float p) { this->p = p; }
	static e* s_getPointer(lua_State * l, int n)
	{
		void* ptr = luaL_testudata(l, n, "MetaEnemy");
		e* emyPtr = nullptr;
		if (ptr)
			emyPtr = *(e**)ptr;
		return emyPtr;
	}

	static int s_setPos(lua_State * l)
	{
		e* emy = s_getPointer(l, 1);

		if (emy)
			emy->setPos(5);

		return 0;
	}

	void hpChange(float hp) { this->hp -= hp; }
	bool isDead() const { return hp <= 0; }
};


class Eh
{
public:
	Eh();
	~Eh();
	static int s_createEnemy(lua_State* ls)
	{
		const char * name = lua_tostring(ls, 1);

		if (name != nullptr)
		{
			e** emy = reinterpret_cast<e**>(lua_newuserdata(ls, sizeof(e*)));
			*emy = new e();
			(*emy)->setName(name);

			luaL_getmetatable(ls, "MetaEnemy");
			lua_setmetatable(ls, -2);
		}
		return 1;
	}
};



int main()
{
	OurLua ol("test2.Lua");

	std::string metaName = "MetaEnemy";
	luaL_Reg luaFunc[] = 
	{
		{"new", Eh::s_createEnemy},
		{"setPosition", e::s_setPos},
		{NULL, NULL}
	};
	std::string luaClassName = "Enemy";

	ol.PushClassFunctions(metaName, luaFunc, luaClassName);

	ol.InitLua();
	ol.Update();


	system("pause");
	return 0;
}