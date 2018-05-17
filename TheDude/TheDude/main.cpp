#include <chrono>
#include "Game.hpp"
#include "GameTime.hpp"
#include "RenderQueue.hpp"

#define CHECK_MEMORY_LEAKS _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF)

const std::string gameTitle = "theDude!";

void CheckPollEvents(sf::RenderWindow * wnd);

int main()
{
	CHECK_MEMORY_LEAKS;

	sf::RenderWindow window(sf::VideoMode(1280, 720), gameTitle);
	
	GameTime gameTime;
	Game game;
	game.Init(&window);

	gameTime.Init();
	while (window.isOpen())
	{
		window.clear();
		Render::g_renderQueue.clear();

		gameTime.UpdateGameTime();

		while (gameTime.AllowedToUpdate())
		{
			game.update();
		}

		CheckPollEvents(&window);

		game.draw();

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
