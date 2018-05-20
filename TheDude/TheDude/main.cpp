#include <chrono>
#include "States\Game.hpp"
#include "States/MainMenu.hpp"
#include "GameTime.hpp"
#include "RenderQueue.hpp"
#include "Level\Level.hpp"

// ImGui
#include "imgui.h"
#include "imgui-SFML.h"
#include <SFML/System/Clock.hpp>
// ImGui

extern "C" {
	_declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}
#define CHECK_MEMORY_LEAKS _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF)

const std::string gameTitle = "theDude!";

void CheckPollEvents(sf::RenderWindow * wnd);

int main()
{
	CHECK_MEMORY_LEAKS;
	sf::RenderWindow window(sf::VideoMode(1280, 720), gameTitle, sf::Style::Titlebar);
	std::stack<State*> states;
	State::InitState(&window, &states);

	ImGui::SFML::Init(window);

	GameTime gameTime;
	
	states.push(new MainMenu());
	
	gameTime.Init();
	sf::Clock clock;
	sf::Color clearColor(127, 255, 127);

	while (!states.empty())
	{
		
		window.clear(clearColor);
		
		Render::g_renderQueue.clear();

		gameTime.UpdateGameTime();
		CheckPollEvents(&window);
		ImGui::SFML::Update(window, clock.restart());

		if (window.hasFocus())
		{
			while (gameTime.AllowedToUpdate())
			{
				if (!states.empty())
					states.top()->Update();

			}
		}
		else
		{
			gameTime.UpdateGameTime();
			gameTime.AllowedToUpdate();
		}


		if (!states.empty())
			states.top()->Draw();
		ImGui::SFML::Render(window);
		
		
		
		window.display();
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
		{
			wnd->close();
		}
	}
}
