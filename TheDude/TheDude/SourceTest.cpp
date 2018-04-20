#include "Scripts/OurLua.h"
#include <iostream>
static int thisIsTest(lua_State * L)
{

	std::cout << "PRINT" << std::endl;

	return 0;
}

class Fuck
{
private:
	int m_pos;
	OurLua ol;

public:
	Fuck() :ol("test.Lua")
	{
		m_pos = 0;

		ol.PushClassFunction(this, Fuck::S_setPosition, "setPos");
		ol.InitLua();
	};
	void setPosition(int pos)
	{
		m_pos = pos;
	}
	int getPosition() { return m_pos; };

	static int S_setPosition(lua_State * L)
	{
		auto f = OurLua::getClassPointer<Fuck>(L);
		if (f)
		{
			auto newPos = OurLua::GetIntegers(L,1);

			f->setPosition(newPos[0]);

		}
		else
		{
			std::cout << "FELL";
		}

		return 0;
	}
};


int main()
{
	Fuck f;
	
	std::cout << f.getPosition() << std::endl;

	system("Pause");

	return true;
}


