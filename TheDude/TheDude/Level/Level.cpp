#include "Level.hpp" 
#include <fstream> 
#include <sstream> 
#include <iostream> 

Level::Level(sf::RenderWindow* renderWindow)
{
	m_pWindow = renderWindow;
	m_grid = nullptr;
	m_camera = nullptr;
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
					sscanf_s(currentLine.c_str(), "%*s %d %d %d %d %d %d %d", &x, &y, &sx, &sy, &r, &g, &b);

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
					int w, h, s, t;

					sscanf_s(currentLine.c_str(), "%*s %i %i %i %i", &w, &h, &s, &t);

					if (m_grid)
						delete m_grid;
					m_grid = nullptr;
					m_grid = new Grid(w, h, static_cast<float>(s), t);
				}
				else if (type == "cam")
				{
					int x, y;
					sscanf_s(currentLine.c_str(), "%*s %i %i", &x, &y);

					sf::Vector2u wSize = m_pWindow->getSize();

					if (m_camera)
						delete m_camera;
					m_camera = nullptr;
					m_camera = new Camera(x, y, wSize.x, wSize.y);
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
	_handleInput();
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
	if (m_camera) delete m_camera;
	m_camera = nullptr;
}

void Level::_copy(const Level & other)
{
	m_grid = new Grid(*other.m_grid);
}
#include "imgui.h"
#include "imgui-SFML.h"
void Level::_handleInput()
{
	ImGui::BeginMainMenuBar();
		
	if (ImGui::BeginMenu("File"))
	{
		if (ImGui::BeginMenu("New")) 
		{
			
			ImGui::EndMenu();
			
		}
		if (ImGui::MenuItem("Open"))
		{
			
		}
		if (ImGui::MenuItem("Save"))
		{
		
		}
		
		ImGui::EndMenu();
	}
		
	
	ImGui::EndMainMenuBar();
	ImGui::Begin("Tools");
	
	if (ImGui::Button("PlaceColor"))
	{
		static float col[3] = { 0 };


		ImGui::ColorPicker3("Colors", col);


		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2i mp = sf::Mouse::getPosition(*m_pWindow) - sf::Vector2i(m_camera->getPosition());
			sf::Vector2i index = mp / static_cast<int>(m_grid->getTile(0, 0).getSize().x + 0.5f);

			if (index.x >= 0 && index.y >= 0 && index.x < m_grid->getWidth() && index.y < m_grid->getHeight())
			{
				m_grid->setColorOfTile(index.x, index.y, col[0] * 256, col[1] * 256, col[2] * 256);
			}

		}
	}

	
	ImGui::End();
}
