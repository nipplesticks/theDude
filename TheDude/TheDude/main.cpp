#include <chrono>
#include "States/Game.hpp"
#include "States/MainMenu.hpp"
#include "GameTime.hpp"
#include "RenderQueue.hpp"
#include "Level\Level.hpp"

// ImGui
#include "imgui.h"
#include "imgui-SFML.h"
#include <SFML/System/Clock.hpp>
// ImGui


#define CHECK_MEMORY_LEAKS _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF)

const std::string gameTitle = "theDude!";

void CheckPollEvents(sf::RenderWindow * wnd);

int main()
{
	CHECK_MEMORY_LEAKS;
	sf::RenderWindow window(sf::VideoMode(1280, 720), gameTitle);
	std::stack<State*> states;
	State::InitState(&window, &states);

	sf::RenderWindow window(sf::VideoMode(1280, 720), gameTitle);
	ImGui::SFML::Init(window);

	GameTime gameTime;
	Game game;
	Level level(&window);
	level.LoadLevel("Resourses/Levels/test34");

	game.Init(&window);
	GameTime gameTime;
	
	states.push(new MainMenu());

	
	gameTime.Init();
	sf::Clock clock;
							// V THIS IS FOR THE MENU LATER
	while (window.isOpen() && level.isClose())
	while (!states.empty())
	{
		window.clear();

		Render::g_renderQueue.clear();

		gameTime.UpdateGameTime();
		CheckPollEvents(&window);
		ImGui::SFML::Update(window, clock.restart());

		while (gameTime.AllowedToUpdate())
		{
			if (!states.empty())
				states.top()->Update();
			//game.update();
			level.Update();
		}
		level.EditorRender();
		window.draw(level);
		ImGui::SFML::Render(window);
		window.display();
	//	game.draw();

		CheckPollEvents(&window);

		if (!states.empty())
			states.top()->Draw();

		if (gameTime.HasTimePassed(1000.0f))
		{
			std::string title;
			title += gameTitle;
			title += gameTime.GetAndResetStats();
			window.setTitle(sf::String(title));
		}
	}
	ImGui::SFML::Shutdown();
	window.close();
	return 0;
}

void CheckPollEvents(sf::RenderWindow * wnd)
{
	sf::Event event;
	while (wnd->pollEvent(event))
	{
		ImGui::SFML::ProcessEvent(event);
		if (event.type == sf::Event::Closed)
			wnd->close();
	}
}
