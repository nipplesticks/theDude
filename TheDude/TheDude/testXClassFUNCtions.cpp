#include "Scripts/OurLua.h"
#include <iostream>
#include <vector>
#include <string>
#include "Entity\Enemy.hpp"
#include "Entity\TheDude.h"
#include <chrono>
#include <Windows.h>

#define NO false
#define YES true

std::vector<sf::Shape*> Render::renderQueue;

const float REFRESH_RATE = 60.0f;
const std::string gameTitle = "theDude!";




void initEmy(OurLua & ol)
{
	luaL_Reg func[]
	{
		{"Create", Enemy::s_CreateEnemy},
		{"setPosition", Enemy::s_setPosition},
		{"setColor", Enemy::s_setColor},
		{"move", Enemy::s_move},
		{"draw", Enemy::s_draw},
		{"__gc", Enemy::s_DestroyEnemy},
		{NULL, NULL}
	};
	ol.PushClassFunctions(Enemy::meta, func, "Enemy");
}

int isKeyPressed(lua_State * l)
{
	std::string key = OurLua::getStrings(l, 1)[0];
	std::vector<bool> s;
	s.push_back(NO);
	if (GetAsyncKeyState(static_cast<int>(key[0])))
		s[0] = YES;
	OurLua::setBooleans(l, s);
	return 1;
}

void initPlayer(OurLua & ol)
{
	luaL_Reg func[]
	{
	{ "Create", TheDude::s_CreateTheDude },
	{ "setPosition", TheDude::s_setPosition },
	{ "setColor", TheDude::s_setColor },
	{ "move", TheDude::s_move },
	{ "draw", TheDude::s_draw },
	{ "__gc", TheDude::s_DestroyTheDude },
	{ NULL, NULL }
	};
	ol.PushClassFunctions(TheDude::meta, func, "Player");
}



int main()
{
	OurLua ol("Scripts/EnemyHandler.Lua");
	initEmy(ol);
	ol.InitLua();

	OurLua lo("Scripts/PlayerHandler.Lua");
	initPlayer(lo);
	lo.PushFunction(isKeyPressed, "isKeyPressed");

	lo.InitLua();

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	sf::RenderWindow window(sf::VideoMode(1280, 720), gameTitle);

	using namespace std::chrono;
	auto time = steady_clock::now();
	auto timer = steady_clock::now();
	int updates = 0;
	int fpsCounter = 0;
	float freq = 1000000000.0f / REFRESH_RATE;
	float unprocessed = 0;

	while (window.isOpen())
	{
		window.clear();
		Render::renderQueue.clear();
		sf::Vector2i mp = sf::Mouse::getPosition(window);
		auto currentTime = steady_clock::now();
		auto dt = duration_cast<nanoseconds>(currentTime - time).count();
		time = currentTime;

		unprocessed += dt / freq;

		while (unprocessed > 1)
		{
			updates++;
			unprocessed -= 1;
			ol.Update();
			lo.Update();
		}

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		ol.Draw();
		lo.Draw();
		
		fpsCounter++;
		for (size_t i = 0; i < Render::renderQueue.size(); i++)
		{
			sf::Shape* s = Render::renderQueue[i];
			window.draw(*s);
		}

		window.display();

		if (duration_cast<milliseconds>(steady_clock::now() - timer).count() > 1000)
		{
			std::string title;
			title += gameTitle;
			title += " | Fps ";
			title += std::to_string(fpsCounter);
			title += " | Tick ";
			title += std::to_string(updates);
			window.setTitle(sf::String(title));
			updates = 0;
			fpsCounter = 0;
			timer += milliseconds(1000);
		}
	}

	//conThread.join();
	return 0;
}