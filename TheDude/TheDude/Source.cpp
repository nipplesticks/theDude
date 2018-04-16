#ifdef _DEBUG
#pragma comment(lib, "LuaLibd.lib")
#else
#pragma comment(lib, "Lualib.lib")
#endif

#include <lua.hpp>
#include <SFML\Graphics.hpp>
#include <Windows.h>
#include <iostream>
#include <thread>
#include "lua.h"
#include <chrono>

#include "Level\Level.hpp"
#include <fstream>

const float REFRESH_RATE = 60.0f;
const std::string gameTitle = "theDude!";

void ConsoleThread(lua_State* L) {
	char command[1000];
	while (GetConsoleWindow()) {
		memset(command, 0, 1000);
		std::cin.getline(command, 1000);
		if (!strcmp(command, "exit"))
			break;
		if (luaL_loadstring(L, command) || lua_pcall(L, 0, 0, 0))
			std::cout << lua_tostring(L, -1) << '\n';
	}
}

int main()
{
	/*lua_State* L = luaL_newstate();
	luaL_openlibs(L);
	std::thread conThread(ConsoleThread, L);*/
	sf::RenderWindow window(sf::VideoMode(1280, 720), gameTitle);

	Level l1;
	l1.LoadLevel("Resourses/Levels/test.chef");

	/*Grid g(32, 32, 32);

	for (int i = 0; i < 32; i++)
	{
		for (int k = 0; k < 32; k++)
		{
			g.setColorOfTile(i, k, i * 8, k * 8, (i + k) * 4);
		}
	}
	
	std::string map = g.toFile();
	std::ofstream file;
	file.open("Resourses/Levels/test.chef");
	file << map;
	file.close();*/

	using namespace std::chrono;
	auto time = steady_clock::now();
	auto timer = steady_clock::now();
	int updates = 0;
	int fpsCounter = 0;
	float freq = 1000000000.0f / REFRESH_RATE;
	float unprocessed = 0;

	while (window.isOpen())
	{
		auto currentTime = steady_clock::now();
		auto dt = duration_cast<nanoseconds>(currentTime - time).count();
		time = currentTime;

		unprocessed += dt / freq;

		while (unprocessed > 1)
		{
			updates++;
			unprocessed -= 1;

		}

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		fpsCounter++;
		window.draw(l1);
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