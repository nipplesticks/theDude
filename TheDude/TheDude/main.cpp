#include <chrono>
#include "States/Game.hpp"
#include "States/MainMenu.hpp"
#include "GameTime.hpp"
#include "RenderQueue.hpp"

#define CHECK_MEMORY_LEAKS _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF)

const std::string gameTitle = "theDude!";

void CheckPollEvents(sf::RenderWindow * wnd);

int main()
{
	CHECK_MEMORY_LEAKS;
	sf::RenderWindow window(sf::VideoMode(1280, 720), gameTitle);
	std::stack<State*> states;
	State::InitState(&window, &states);

	GameTime gameTime;
	
	states.push(new MainMenu());

	
	gameTime.Init();
	while (!states.empty())
	{
		window.clear();
		Render::g_renderQueue.clear();

		gameTime.UpdateGameTime();

		while (gameTime.AllowedToUpdate())
		{
			if (!states.empty())
				states.top()->Update();
		}

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

	return 0;
}

void CheckPollEvents(sf::RenderWindow * wnd)
{
	sf::Event event;
	while (wnd->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			wnd->close();
	}
}
