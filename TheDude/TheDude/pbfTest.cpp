#include <SFML\Graphics.hpp>
#include <chrono>
#include <iostream>
#include <time.h>

const float REFRESH_RATE = 60.0f;
const sf::Vector2f GRAVITY(0.0f, 9.82f);


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
	s.setRadius(10.0f);
	s.setOrigin(s.getRadius(), s.getRadius());
	s.setFillColor(sf::Color::Blue);

	for (int i = 0; i < COUNT; i++)
	{
		p[i].shape = s;
		p[i].shape.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
		p[i].mass = 0.001f;
		p[i].position.x = (g_window.getSize().x / 2) - ((COUNT / 2) * p[i].shape.getRadius() * 2) + (i * p[i].shape.getRadius() * 2);
		p[i].position.y = g_window.getSize().y / 2;
		p[i].velocity.x = rand() % 20 * ((rand() % 2 == 0) ? -1 : 1);
		p[i].velocity.y = rand() % 20 * ((rand() % 2 == 0) ? -1 : 1);
		p[i].shape.setPosition(p[i].position.x, p[i].position.y);
	}

	/*p[0].position.x = 500;
	p[0].position.y = 500;
	p[0].velocity.x = 1;
	p[0].velocity.y = 0;
	p[0].shape.setPosition(p[0].position.x, p[0].position.y);

	p[1].position.x = 600;
	p[1].position.y = 500;
	p[1].velocity.x = -1;
	p[1].velocity.y = 0;
	p[1].shape.setPosition(p[1].position.x, p[1].position.y);*/

}

void calculateForces(float dt)
{
	bool inside = true;

	for (auto & par : p)
	{
		sf::Vector2f force;
		force += par.mass * GRAVITY;
		while (inside)
		{
			inside = false;
			for (auto & par2 : p)
			{
				sf::Vector2f p1 = par.position;
				if (&par != &par2)
				{
					sf::Vector2f p2 = par2.position;

					sf::Vector2f dist = p2 - p1;

					float dstSqrd = abs(dist.x * dist.x + dist.y * dist.y);
					float radSqrd = (par.shape.getRadius() + par2.shape.getRadius()) * (par.shape.getRadius() + par2.shape.getRadius());

					if (dstSqrd < radSqrd)
					{
						// Collision
						inside = true;
						
						sf::Vector2f hw = (p1 + p2) * 0.5f;
						par2.position = hw + (dist / (sqrt(dstSqrd))) * (par2.shape.getRadius() * 1.01f);
						par2.shape.setPosition(par2.position);
						par.position = hw - (dist / (sqrt(dstSqrd))) * (par.shape.getRadius() * 1.01f);
						par.shape.setPosition(par.position);

						sf::Vector2f force2 = (par2.velocity / dt) * par2.mass;
						force += force2;
					}


				}
			}
		}
		

		sf::Vector2f acc = force / par.mass;
		par.velocity += (acc * dt);
	}
}

void move(Particle &par)
{
	if (par.position.y + par.shape.getRadius() * 2 > g_window.getSize().y)
	{
		par.position.y = g_window.getSize().y - par.shape.getRadius();
		par.velocity.y *= -0.7;
	}
	else if (par.position.y < 0)
	{
		par.position.y = par.shape.getRadius();
		par.velocity.y *= -0.7;
	}

	if (par.position.x + par.shape.getRadius() * 2 > g_window.getSize().x)
	{
		par.position.x = g_window.getSize().x - par.shape.getRadius();
		par.velocity.x *= -0.7;
	}
	else if (par.position.x < 0)
	{
		par.position.x = par.shape.getRadius();
		par.velocity.x *= -0.7;
	}

	par.position += par.velocity;
	par.shape.setPosition(par.position.x, par.position.y);

	int i = 0;
}

void update(float dt)
{
	calculateForces(dt);

	for (auto & par : p)
	{
		move(par);
	}
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
	srand(static_cast<unsigned>(time(0)));
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	init();

	bool wasPressed = false;

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
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !wasPressed)
			{
				wasPressed = true;
			}
			else if (wasPressed && !sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				wasPressed = false;
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