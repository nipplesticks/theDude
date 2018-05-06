#include "Level.hpp" 
#include <fstream> 
#include <sstream> 
#include <iostream> 
#include <filesystem>
#include "imgui.h"
#include "imgui-SFML.h"

Level::Level(sf::RenderWindow* renderWindow)
{
	m_pWindow = renderWindow;
	m_grid = nullptr;
	m_camera = nullptr;
	m_closeFlag = false;
	m_spritePaletteOpen = true;
	m_entityPaletteOpen = true;
	
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
	delete m_grid;
	m_grid = nullptr;
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
				if (type == "sheet")
				{
					std::string path;
					stream >> path;
					//TODO HENRIK
					m_grid->LoadSpriteSheet(path);
					
							
				}
				else if (type == "t")
				{
					int x, y, t, r, g, b, itx, ity;
					sscanf_s(currentLine.c_str(), "%*s %d %d %d %d %d %d %d %d", &x, &y, &t, &r, &g, &b, &itx, &ity);
					m_grid->setTypeOfTile(x, y, t);
					m_grid->setColorOfTile(x, y, r, g, b);

					m_grid->setTextureOfTile(x, y, sf::IntRect(itx, ity, 32, 32));

					
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
					m_camera = new Camera(static_cast<float>(x), static_cast<float>(y), wSize.x, wSize.y);
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

bool Level::SaveLevel(const std::string & target)
{
	std::ofstream map;
	map.open(target);
	if (map)
	{
		map << "cam 100 0\n";
		map << m_grid->toFile();
		return true;
	}
	return false;
}

void Level::Update()
{
	m_camera->update();
	m_grid->update(m_camera);
}

void Level::EditorRender()
{	
	_toolbarRender();
	
	if(m_spritePaletteOpen)
		_spritePaletteRender();
	if(m_entityPaletteOpen)
		_entityPaletteRender();
	if(m_tileTypePaletteOpen)
		_tileTypePaletteRender();

}

bool Level::isClose()
{
	return !m_closeFlag;
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

void Level::_toolbarRender()
{
	ImGui::BeginMainMenuBar();

	if (ImGui::BeginMenu("File"))
	{
		if (ImGui::BeginMenu("New"))
		{
			static float dim[2] = { 1, 1 };
			dim[0] = std::max(dim[0], 1.0f);
			dim[1] = std::max(dim[1], 1.0f);
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
			static auto files = filesInDir("Resourses/Levels/");
			
			for (auto& s : files)
			{
				if (ImGui::MenuItem(s.c_str()))
				{
					s.erase(s.begin());
					LoadLevel("Resourses/Levels/" + s);
				}

			}
			ImGui::EndMenu();
		}
		static bool saved = false;
		if (ImGui::BeginMenu("Save"))
		{
			static char name[20] = {};

			ImGui::InputText("File path", name, 20);
			if (ImGui::Button("Save"))
			{
				std::string path = "Resourses/Levels/";
				saved = SaveLevel(path + std::string(name));


			}
			if (saved)
				ImGui::BulletText("Saved Succ");
			ImGui::EndMenu();
		}
		else
			saved = false;

		if (ImGui::MenuItem("Exit"))
		{
			m_closeFlag = true;
		}
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("Tools"))
	{
		m_spritePaletteOpen = ImGui::MenuItem("Spritesheet") ? true : m_spritePaletteOpen;
		m_entityPaletteOpen = ImGui::MenuItem("Entities") ? true : m_entityPaletteOpen;
		m_tileTypePaletteOpen = ImGui::MenuItem("Tile Type") ? true : m_tileTypePaletteOpen;

		ImGui::EndMenu();
	}

	ImGui::BulletText(m_currentTool.c_str());
	
	ImGui::EndMainMenuBar();
}

void Level::_spritePaletteRender()
{
	static sf::Vector2u imgSize;
	static int size = 32;
	

	ImGui::Begin("SpriteSheet", &m_spritePaletteOpen);
	static bool functional = false;
	if (isClickInside())
	{
		m_currentTool = "Current Tool: Sprite Palette";
		_changeCurrentTool()
		m_activeTool[0] = true;
		m_activeTool[1] = false;
		m_activeTool[2] = false;
		m_grid->NormalMode();

	}

	if (!m_grid->isSpritesheetLoaded())
	{
		static char path[20];

		ImGui::InputText("Path", path, 20, ImGuiInputTextFlags_CharsNoBlank);

		ImGui::InputInt("Sprite Size", &size);

		if (ImGui::Button("Load"))
		{

			std::string fullPath = "Resourses/SpriteSheet/";
			fullPath += std::string(path);
		
			m_grid->LoadSpriteSheet(fullPath);
			imgSize = m_grid->getSheetImageSize();
			
			
		}


	}
	else
	{
		ImVec2 p = ImGui::GetCursorScreenPos();
		ImVec2 l = ImGui::GetMousePos();
		ImVec2 s = ImGui::GetWindowSize();

		l = ImVec2(l.x - p.x, l.y - p.y);
		imgSize = m_grid->getSheetImageSize();

		// Get the full spriteSheet from grid

		ImGui::Image(m_grid->getDisplaySprite());
		
		static sf::IntRect rect = sf::IntRect(0,0,size,size);


		if (l.x > 0 && l.y > 0 && l.x <= imgSize.x && l.y <= imgSize.y&& ImGui::IsMouseClicked(0))
		{
			std::cout << "Inside" << std::endl;
			int poweroftwo = std::log(size) / std::log(2);
			rect.left = ((int)l.x >> poweroftwo) << poweroftwo;
			rect.top = ((int)l.y >> poweroftwo) << poweroftwo;
			rect.width = size;
			rect.height = size;

			
		}

		ImVec2 a = ImVec2(p.x + rect.left, p.y + rect.top);
		ImVec2 b = ImVec2(p.x + rect.left + rect.width, p.y + rect.top + rect.height);

		ImGui::GetWindowDrawList()->AddRect(a, b, IM_COL32(255, 0, 0, 255), 3.0f, 15, 3.0f);

		if (m_activeTool[0])
		{
			if (l.x < 0 || l.y < 0)
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					sf::Vector2i mp = sf::Mouse::getPosition(*m_pWindow) - sf::Vector2i(m_camera->getPosition());
					sf::Vector2i index = mp / static_cast<int>(m_grid->getTile(0, 0).getSize().x + 0.5f);

					if (index.x >= 0 && index.y >= 0 && index.x < m_grid->getWidth() && index.y < m_grid->getHeight())
					{

						m_grid->setTextureOfTile(index.x, index.y, rect);

					}

				}
			}
		}
		
	}
	ImGui::End();
}

void Level::_entityPaletteRender()
{

	ImGui::Begin("Entities", &m_entityPaletteOpen);
	
	if (isClickInside())
		_changeCurrentTool(TOOL_ENTITY, "Entity Palette", true);
	
	static char name[20];
	ImGui::InputText("Lua File", name, 20);

	auto strs = filesInDir("Resourses/Levels");
	
	ImGui::Button("Load Entity");

	ImGui::End();
}

void Level::_tileTypePaletteRender()
{
	ImGui::Begin("Tile Type", &m_tileTypePaletteOpen);
	if (isClickInside())
	{
		m_currentTool = "Current Tool: Tile Type";
		m_activeTool[0] = false;
		m_activeTool[1] = false;
		m_activeTool[2] = true;
		m_grid->MarkMode();
	}

	static bool selectables[3] = { 1, 0, 0 };
	static int currentType = 0;
	if (ImGui::Selectable("None", &selectables[0]))
	{
		selectables[1] = selectables[2] = false;
		currentType = 0;
	}
	if (ImGui::Selectable("Dangerous", &selectables[1]))
	{
		selectables[0] = selectables[2] = false;
		currentType = 1;
	}
	if (ImGui::Selectable("Solid", &selectables[2]))
	{
		selectables[0] = selectables[1] = false;
		currentType = 2;
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2i mp = sf::Mouse::getPosition(*m_pWindow) - sf::Vector2i(m_camera->getPosition());
		sf::Vector2i index = mp / static_cast<int>(m_grid->getTile(0, 0).getSize().x + 0.5f);

		if (index.x >= 0 && index.y >= 0 && index.x < m_grid->getWidth() && index.y < m_grid->getHeight())
		{

			m_grid->setTypeOfTile(index.x, index.y, currentType);

		}

	}

	ImGui::End();
}

void Level::_tileColorPaletteRender()
{
	ImGui::Begin("Colors", &m_tileColorPaletteOpen);



	ImGui::End();
}

bool Level::isClickInside() const
{
	ImVec2 p = ImGui::GetCursorScreenPos();
	ImVec2 l = ImGui::GetMousePos();
	ImVec2 s = ImGui::GetWindowSize();
	l = ImVec2(l.x - p.x, l.y - p.y);

	return l.x > 0 && l.y > 0 && l.x <= s.x && l.y <= s.y&& ImGui::IsMouseClicked(0);
}

std::vector<std::string> Level::filesInDir(std::string path)
{
	std::vector<std::string> files;

	// Stupid but works
	std::string folderPath = __FILE__;
	folderPath += "/../../" + path;
	namespace fs = std::experimental::filesystem;
	for (auto& p : fs::directory_iterator(folderPath))
	{
		std::stringstream s;
		s << p << std::endl;
		std::string lol(s.str());
		std::string relative;
		for (size_t i = lol.find_last_of('\\'); i < lol.size() - 1; i++)
			relative += lol[i];

		files.push_back(relative);

	}

	return files;
}

void Level::_changeCurrentTool(int index, std::string tool, bool NormalMode)
{
	m_currentTool = "Current Tool: " + tool;
	memset(m_activeTool, 0, sizeof(m_activeTool));
	m_activeTool[index] = true;
	m_grid->NormalMode();
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
