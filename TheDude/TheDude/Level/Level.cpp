#include "Level.hpp" 
#include <fstream> 
#include <sstream> 
#include <iostream> 
#include <filesystem>

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
#include <iostream>
#include <sstream>
void Level::_handleInput()
{
	
	ImGui::BeginMainMenuBar();
	
	if (ImGui::BeginMenu("File"))
	{
		if (ImGui::BeginMenu("New"))
		{

			static float dim[2] = { 0 };

			ImGui::InputFloat2("New Size", dim);

			if (ImGui::Button("Create Level"))
			{
				delete m_grid;
				m_grid = new Grid(dim[0], dim[1]);
			}


			ImGui::EndMenu();

		}
		if (ImGui::BeginMenu("Open"))
		{
			static char name[20] = {};
			ImGui::InputText("File path", name, 20);
			if (ImGui::Button("Open file"))
			{
				LoadLevel(std::string(name));
			}
			ImGui::EndMenu();
		}
		if (ImGui::MenuItem("Save"))
		{

		}

		if (ImGui::MenuItem("Exit"))
		{
			// Exit here
		}
		ImGui::EndMenu();
	}


	ImGui::EndMainMenuBar();
	static 	sf::Image image;
	static bool loadedSpirteSheet = false;
	static sf::Vector2u imgSize;
	static int size = 32;
	ImGui::Begin("SpriteSheet");
	if (!loadedSpirteSheet)
	{
		static char path[20];
		
		ImGui::InputText("Path", path, 20, ImGuiInputTextFlags_CharsNoBlank);
		ImGui::InputInt("Sprite Size", &size);

		if (ImGui::Button("Load"))
		{
			
			std::string fullPath = "Resourses/SpriteSheet/";
			fullPath += std::string(path);

			
			image.loadFromFile(fullPath.c_str());
			m_spriteSheet.loadFromImage(image);
			imgSize = m_spriteSheet.getSize();

			for (int i = 0; i < 1; i++)
			{
				sf::Sprite sprite;
				sprite.setTexture(m_spriteSheet);
				//sprite.setTextureRect(sf::IntRect(256, 0, 32, 32));
				m_sprites.push_back(sprite);
			}
			loadedSpirteSheet = true;
		}

		
	}
	else
	{
		ImVec2 p = ImGui::GetCursorScreenPos();
		ImVec2 l = ImGui::GetMousePos();
		l = ImVec2(l.x - p.x, l.y - p.y);
		
		ImGui::Image(m_sprites[0]);
		if (ImGui::Button("Load new spritesheet"))
			loadedSpirteSheet = false;
		static bool used = false;
		static sf::IntRect rect;
		if (used)
		{
			ImVec2 a = ImVec2(p.x + rect.left, p.y + rect.top);
			ImVec2 b = ImVec2(p.x + rect.left + rect.width, p.y + rect.top + rect.height);

			ImGui::GetWindowDrawList()->AddRect(a,b , IM_COL32(255, 0, 0, 255), 3.0f, 15, 3.0f);
		}

		
		if (l.x > 0 && l.y > 0 && l.x <= imgSize.x && l.y <= imgSize.y&& ImGui::IsMouseClicked(0))
		{
			
			int poweroftwo = std::log(size) / std::log(2);
			rect.left = ((int)l.x >> poweroftwo) << poweroftwo;
			rect.top = ((int)l.y >> poweroftwo) << poweroftwo;
			rect.width = size;
			rect.height = size;
			used = true;
		}

		if (l.x < 0 || l.y < 0)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				sf::Vector2i mp = sf::Mouse::getPosition(*m_pWindow) - sf::Vector2i(m_camera->getPosition());
				sf::Vector2i index = mp / static_cast<int>(m_grid->getTile(0, 0).getSize().x + 0.5f);

				if (index.x >= 0 && index.y >= 0 && index.x < m_grid->getWidth() && index.y < m_grid->getHeight())
				{
					if (used)
					{
						m_grid->setTextureOfTile(index.x, index.y, m_spriteSheet, rect);

					}
				}

			}
		}
	}

	
	
	
		
	

	
	ImGui::End();

	static char name[20];
	ImGui::Begin("Entities");
	ImGui::InputText("Lua File", name, 20);
	std::string folderPath = __FILE__;
	folderPath += "/../../Resourses/Characters";
	namespace fs = std::experimental::filesystem;
	for (auto& p : fs::directory_iterator(folderPath))
	{
		std::stringstream ss;
		std::string filelol;
		ss << p << std::endl;
		ss >> filelol;
		std::cout << filelol << std::endl;
		
	}
	ImGui::Button("Load Entity");
	ImGui::End();
}
