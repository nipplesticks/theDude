#include "Level.hpp" 
#include <fstream> 
#include <sstream> 
#include <iostream> 

Level::Level()
{
	m_grid = nullptr;
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
					int x, y, t, r, g, b;
					sscanf_s(currentLine.c_str(), "%*s %d %d %d %d %d %d", &x, &y, &t, &r, &g, &b);
					m_grid->setTypeOfTile(x, y, t);
					m_grid->setColorOfTile(x, y, r, g, b);
				}
				else if (type == "e")
				{
					// posX, posY, sizeX, sizeY, type
					int x, y, sx, sy, t, r, g, b;
					sscanf_s(currentLine.c_str(), "%*s %d %d %d %d %d %d %d %d", &x, &y, &sx, &sy, &t, &r, &g, &b);

					/*
						Create Enemy
					*/

				}
				else if (type == "i")
				{
					// posX, posY, sizeX, sizeY, type
					int x, y, sx, sy, t, r, g, b;
					sscanf_s(currentLine.c_str(), "%*s %d %d %d %d %d %d %d %d", &x, &y, &sx, &sy, &t, &r, &g, &b);

					/*
						Create item
					*/
				}
				else if (type == "theDude")
				{
					// posX, posY, sizeX, sizeY
					int x, y, sx, sy, r, g, b;
					sscanf_s(currentLine.c_str(), "%*s %d %d %d %d %d %d %d %d", &x, &y, &sx, &sy, &r, &g, &b);

					/*
						Create theDude
					*/
				}
				else if (type == "name")
				{
					std::getline(stream, m_levelName);
				}
				else if (type == "grid")
				{
					int w, h, t;
					float s;

					sscanf_s(currentLine.c_str(), "%*s %i %i %f %i", &w, &h, &s, &t);
					m_grid = new Grid(w, h, s, t);
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
	target.draw(*m_grid, states);
}

void Level::_cleanup()
{
	if (m_grid)
		delete m_grid;
	m_grid = nullptr;
}

void Level::_copy(const Level & other)
{
	m_grid = new Grid(*other.m_grid);
}