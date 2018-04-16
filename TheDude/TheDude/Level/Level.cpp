#include "Level.hpp" 
#include <fstream> 
#include <sstream> 
#include <iostream> 

Level::Level()
{
	m_camera = new Camera(0, 0, 10,10);
	m_grid = new Grid();
	for (int i = 0; i < 32; i++)
	{
		for (int k = 0; k < 32; k++)
		{
			m_grid->setColorOfTile(i, k, i * 8, k * 8, (i + k) * 4);
		}
	}
	m_levelName = "";
}

Level::Level(const Level & other)
{
	_cleanup();
	_copy(other);
}

Level::~Level()
{
	_cleanup();
}

void Level::LoadLevel(const std::string & target)
{
	std::ifstream map;
	map.open(target);
	if (map)
	{
		std::string currentLine = "";

		while (std::getline(map, currentLine))
		{
			if (currentLine[0] != '#' && currentLine != "" && currentLine[0] != ' ')
			{
				std::string type = "";
				std::stringstream stream(currentLine);

				stream >> type;

				if (type == "t")
				{
					int x, y, t;

					scanf_s(currentLine.c_str(), "%*s %d %d %d", &x, &y, &t);


				}
				else if (type == "name")
				{
					std::getline(stream, m_levelName);
				}

			}
		}

		map.close();
	}
	else
	{
		std::cout << "Could not open " << target << " please dont suck\n";
	}
}

void Level::Update()
{
	m_camera->update();
	m_grid->update(m_camera);
}

Level & Level::operator=(const Level & other)
{
	if (this != &other)
	{
		_cleanup();
		_copy(other);
	}

	return *this;
}

void Level::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(*m_grid);
}

void Level::_cleanup()
{
	if (m_grid)
		delete m_grid;
	m_grid = nullptr;
	if (m_camera) delete m_camera;
	m_camera = nullptr;
}

void Level::_copy(const Level & other)
{
	m_grid = new Grid(*other.m_grid);
}