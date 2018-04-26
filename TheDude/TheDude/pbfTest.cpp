#include <SFML\Graphics.hpp>
#include <chrono>
#include <iostream>

const float REFRESH_RATE = 60.0f;
const sf::Vector2f GRAVIRY(0.0f, -9.82f);


struct Particle
{
	sf::CircleShape		shape;
	sf::Vector2f		position;
	sf::Vector2f		velocity;
	float				denisty;
	float				mass;
};

// Globals
const std::string gameTitle = "PBF!";
sf::RenderWindow g_window(sf::VideoMode(1280, 720), gameTitle);
const int COUNT = 10;
Particle p[COUNT];

void init()
{
	sf::CircleShape s;
	s.setRadius(3.0f);
	s.setFillColor(sf::Color::Blue);

	for (int i = 0; i < COUNT; i++)
	{
		p[i].shape = s;
		p[i].mass = 0.001f;
		p[i].position.x = i * 6.0f;
		p[i].position.y = i * 6.0f;
		p[i].velocity.x = 0.0f;
		p[i].velocity.y = 0.0f;
		p[i].shape.setPosition(p[i].position.x, p[i].position.y);
	}

}

void update(float dt)
{

}

void draw()
{
	g_window.clear();

	for (int i = 0; i < COUNT; i++)
		g_window.draw(p[i].shape);
	g_window.display();
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	init();

	using namespace std::chrono;
	auto time = steady_clock::now();
	auto timer = steady_clock::now();
	int updates = 0;
	int fpsCounter = 0;
	float freq = 1000000000.0f / REFRESH_RATE;
	float unprocessed = 0;

	while (g_window.isOpen())
	{
		auto currentTime = steady_clock::now();
		auto dt = duration_cast<nanoseconds>(currentTime - time).count();
		time = currentTime;

		unprocessed += dt / freq;

		while (unprocessed > 1)
		{
			updates++;
			unprocessed -= 1;

			update(1.0f / REFRESH_RATE);
		}

		sf::Event event;
		while (g_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				g_window.close();
		}
		draw();
		fpsCounter++;
		if (duration_cast<milliseconds>(steady_clock::now() - timer).count() > 1000)
		{
			std::string title;
			title += gameTitle;
			title += " | Fps ";
			title += std::to_string(fpsCounter);
			title += " | Tick ";
			title += std::to_string(updates);
			g_window.setTitle(sf::String(title));
			updates = 0;
			fpsCounter = 0;
			timer += milliseconds(1000);
		}
	}

	//conThread.join();
	return 0;
}