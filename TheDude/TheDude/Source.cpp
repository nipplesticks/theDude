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

#include "Camera\Camera.hpp"
#include "Level\Level.hpp"
#include "States\MainMenu.hpp"

#include <fstream>
#include "Interface\Button.hpp"

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
void yes()
{
	std::cout << "JAG TRYCKTES" << std::endl;
}
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	/*lua_State* L = luaL_newstate();
	luaL_openlibs(L);
	std::thread conThread(ConsoleThread, L);*/
	sf::RenderWindow window(sf::VideoMode(1280, 720), gameTitle);


	std::stack<State*> stateStack;
	State::initStatics(&stateStack, &window);
	MainMenu * s = new MainMenu();
	stateStack.push(s);
	
	using namespace std::chrono;
	auto time = steady_clock::now();
	auto timer = steady_clock::now();
	int updates = 0;
	int fpsCounter = 0;
	float freq = 1000000000.0f / REFRESH_RATE;
	float unprocessed = 0;
	Button lol(200, 200, 100 * (16.0f / 9.0f), 100 );
	lol.setFunctionPointer(yes);
	

	while (window.isOpen())
	{
		sf::Vector2i mp = sf::Mouse::getPosition(window);
		lol.update(mp);
		auto currentTime = steady_clock::now();
		auto dt = duration_cast<nanoseconds>(currentTime - time).count();
		time = currentTime;

		unprocessed += dt / freq;

		while (unprocessed > 1)
		{
			updates++;
			unprocessed -= 1;
			
			if (!stateStack.empty())
				stateStack.top()->Update();
			else
				window.close();
		}

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}


		window.clear();
		fpsCounter++;
		
		if (!stateStack.empty())
			stateStack.top()->Draw();
		window.draw(lol);
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