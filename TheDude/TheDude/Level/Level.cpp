#include "Level.hpp" 
#include <fstream> 
#include <sstream> 
#include <iostream> 
#include <filesystem>
#include <algorithm>
#include "imgui.h"
#include "imgui-SFML.h"
#include <array>

Level::Level(sf::RenderWindow* renderWindow)
{
	m_pWindow = renderWindow;
	m_loadedSprites = false;
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
	_cleanup();
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
				if (type == "sp")
				{
					std::string spritePath;
					stream >> spritePath;

					m_entityInstanceTextures.push_back(TextureWPath());
					m_entityInstanceTextures.back().path = spritePath;
					m_entityInstanceTextures.back().texture.loadFromFile(spritePath);

					m_entityTexGroups.push_back(EntityTexGroup());
					m_entityTexGroups.back().texturePath = spritePath;

				}
				else if (type == "p")
				{
					m_entitesForLua.push_back(EntityShape());
					m_entitesForLua.back().shape = sf::RectangleShape(sf::Vector2f(32, 32));
					m_entitesForLua.back().shape.setTexture(&m_entityInstanceTextures.back().texture);

					int xCoord, yCoord;
					stream >> xCoord >> yCoord;

					sf::Vector2f pos(xCoord, yCoord);

					m_entitesForLua.back().pos = pos;
					m_entitesForLua.back().shape.setPosition(pos);
					
					m_entityTexGroups.back().m_entityPositions.push_back(pos);
					
				
				}
				else if (type == "sheet")
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
	int i = 0;
}

bool Level::SaveLevel(const std::string & target)
{
	std::ofstream map;

	std::string path = "Resourses/Levels/";
	std::string path2 = "Scripts/";
	std::string levelName = path+ target + ".level";
	std::string luaName = path2 + target + ".lua";
	// Levelfile
	map.open(levelName);
	if (map)
	{
		map << "cam 100 0\n";
		for (auto& etg : m_entityTexGroups)
		{
			map << "sp "<< etg.texturePath << "\n";
			for (auto& pos : etg.m_entityPositions)
				map << "p " << pos.x << " " << pos.y << "\n";
		}
		map << m_grid->toFile();
	}

	map.close();

	map.open(luaName);
	
	if(map)
	{
		map << "--Auto generated code based on map\n";
		map << "\n";
		map << "local Entities = {}\n";
		map << "local ENTITYS_AMOUNT = " << m_entitesForLua.size() << "\n";
		map << "\n";
		map << "local function _initEntities()\n";
		for (auto entity : m_entitesForLua)
		{
			map << "\tlocal Entity_Scripted = Character.Create()\n";
			map << "\tEntity_Scripted:AddScript(\"" << entity.luafile << "\")\n";
			map << "\tEntity_Scripted:setPosition(" << entity.pos.x << ","<< entity.pos.y << ")\n";
			map << "\tEntity_Scripted:setSize(" << entity.shape.getSize().x << "," << entity.shape.getSize().y << ")\n";
			map << "\ttable.insert(Entities, Entity_Scripted)\n";
		}
		map << "end\n";
		map << "\n";

		map << "local function _updateEntities()\n";
			map << "\tsetPlayerPosition(Entities[1]:getPosition())\n";
			map << "\tfor i = 1, #Entities, 1 do\n";
				map << "\t\tEntities[i]:Update()\n";
			map << "\tend\n";
		map << "end\n";
		map << "\n";

		map << "local function _drawEntities()\n";
			map << "\tfor i = 1, #Entities, 1 do\n";
				map << "\t\tEntities[i]:Draw()\n";
			map << "\tend\n";
		map << "end\n";
		map << "\n";
		
		map << "local function _collisionHandling()\n";
			map << "\tfor i = 2, #Entities, 1 do\n";
				map << "\t\tisCollision = CheckCollision(Entities[1], Entities[i])";
				map << "\t\tif isCollision then\n";
				map << "\t\t\tEntities[1]:AlterHealth(Entities[i]:getAttack() * -1)\n";
				map << "\t\tend\n";
			map << "\tend\n";
		map << "end\n";
		map << "\n";

		map << "function init()\n";
			map << "\t_initEntities()\n";
		map << "end\n";
		map << "\n";

		map << "function update()\n";
		map << "\tif isKeyPressed(\"ESC\") then\n";
		map << "\t\tExitGame()\n";
		map << "\telseif Entities[1]:isDead() == false then\n";
		map << "\t\tEntities[1]:Update()\n";
		map << "\t\t_updateEntities()\n";
		map << "\t\t_collisionHandling()\n";
		map << "\tend\n";
		map << "end\n";
		map << "\n";

		map << "function draw()\n";
		map << "\t_drawEntities()\n";
		map << "end\n";
	}
	map.close();
	// Lua file
	return true;
}

void Level::Update()
{
	m_camera->update();
	m_grid->update(m_camera);

	for (int  i = 0; i < m_entitesForLua.size(); i++)
	{
		m_entitesForLua[i].shape.setPosition(m_entitesForLua[i].pos + m_camera->getPosition());
	}
	
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
	if (m_tileColorPaletteOpen)
		_tileColorPaletteRender();

	
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
	for (auto& e : m_entitesForLua)
		target.draw(e.shape,states);
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
				m_entityTexGroups.clear();
				m_entitesForLua.clear();
				m_entityInstanceTextures.clear();
				m_loadedSprites = false;
				
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
				
				saved = SaveLevel(std::string(name));


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
		m_tileColorPaletteOpen = ImGui::MenuItem("Tile Colors") ? true : m_tileColorPaletteOpen;

		ImGui::EndMenu();
	}

	ImGui::BulletText(m_currentTool.c_str());
	
	ImGui::EndMainMenuBar();
}

void Level::_spritePaletteRender()
{
	static sf::Vector2u imgSize;

	ImGui::Begin("SpriteSheet", &m_spritePaletteOpen);

	if (_IsClickInside())
		_changeCurrentTool(TOOL_SPRITE, "Sprite Palette", true);

	if (!m_grid->isSpritesheetLoaded())
	{
		static char path[20];
		static int size;
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
		static int tSize = m_grid->getTile(0, 0).getSize().x;

		l = ImVec2(l.x - p.x, l.y - p.y);
		imgSize = m_grid->getSheetImageSize();
		

		// Get the full spriteSheet from grid

		ImGui::Image(m_grid->getDisplaySprite());
	
		
		static sf::IntRect rect = sf::IntRect(0,0, tSize, tSize);


		if (l.x > 0 && l.y > 0 && l.x <= imgSize.x && l.y <= imgSize.y&& ImGui::IsMouseClicked(0))
		{
			int poweroftwo = std::log(tSize) / std::log(2);
			rect.left = ((int)l.x >> poweroftwo) << poweroftwo;
			rect.top = ((int)l.y >> poweroftwo) << poweroftwo;
			rect.width = tSize;
			rect.height = tSize;

			
		}

		ImVec2 a = ImVec2(p.x + rect.left, p.y + rect.top);
		ImVec2 b = ImVec2(p.x + rect.left + rect.width, p.y + rect.top + rect.height);

		ImGui::GetWindowDrawList()->AddRect(a, b, IM_COL32(255, 0, 0, 255), 3.0f, 15, 3.0f);

		if (m_activeTool[TOOL_SPRITE])
		{
			
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !_IsMouseInside())
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
	ImGui::End();
}

void Level::_entityPaletteRender()
{
	ImGui::Begin("Entities", &m_entityPaletteOpen);
	bool wasClickedInside = _IsClickInside();
	if (wasClickedInside)
		_changeCurrentTool(TOOL_ENTITY, "Entity Palette", true);

	static std::string path = "Scripts/";
	static std::vector<std::string> strs = filesInDir(path);
	
	static int currentTextureIndex = -1;
	static sf::Sprite displayTexure;
	static sf::Texture sampleTexture;
	if (!m_loadedSprites)
	{
		sampleTexture.loadFromFile("sample.png");
		displayTexure.setTexture(sampleTexture);
		auto i = std::begin(strs);
		while (i != std::end(strs))
		{
			std::string currentPath;

			currentPath += path + (*i).c_str();
			std::string yes = getTexturePath(currentPath);
			
			if (yes == "")
			{
				i = strs.erase(i);
			}
			else
			{
				
				bool exists = false;
				for (int k = 0; k < m_entityTexGroups.size(); k++)
				{
					if (m_entityTexGroups[k].texturePath == yes)
					{
						exists = true;
					}
				}
				if (!exists)
				{
					m_entityInstanceTextures.push_back(TextureWPath());
					m_entityInstanceTextures.back().texture.loadFromFile(yes);
					m_entityInstanceTextures.back().path = yes;
					(*i).erase((*i).begin());
					std::string luaPath = "Scripts/" + *i;
					m_entityInstanceTextures.back().luafile = luaPath;
					EntityTexGroup etg;
					etg.texturePath = yes;
					m_entityTexGroups.push_back(etg);
				}
				
				i++;
			}

		}
		
		m_loadedSprites = true;

	}
	
	ImGui::Image(displayTexure);
	
	static std::array<bool, 10> selectable{ 0,0,0,0,0,0 };

	for (int i = 0; i < strs.size(); i++)
	{
		if (ImGui::Selectable(strs[i].c_str(), &selectable[i]))
		{
			_resetArray(selectable, i);
			currentTextureIndex = i;
			displayTexure.setTexture(m_entityInstanceTextures[i].texture);
		}

	}

	if (m_activeTool[TOOL_ENTITY])
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !_IsMouseInside())
		{
			sf::Vector2i mp = sf::Mouse::getPosition(*m_pWindow) - sf::Vector2i(m_camera->getPosition());
			sf::Vector2i index = mp / static_cast<int>(m_grid->getTile(0, 0).getSize().x + 0.5f);

			if (index.x >= 0 && index.y >= 0 && index.x < m_grid->getWidth() && index.y < m_grid->getHeight())
			{
				sf::Vector2f position = sf::Vector2f(index.x << 5, index.y << 5);
				bool existing = false;

				for(auto& currentPos : m_entitesForLua)
					if (currentPos.pos == position)
					{
						existing = true;
						break;
					}
				if (!existing)
				{
					
					m_entitesForLua.push_back(EntityShape());
					m_entitesForLua.back().shape = sf::RectangleShape(sf::Vector2f(32, 32));
					m_entitesForLua.back().shape.setTexture(&m_entityInstanceTextures[currentTextureIndex].texture);
					m_entitesForLua.back().shape.setPosition(position + m_camera->getPosition());
					m_entitesForLua.back().luafile = m_entityInstanceTextures[currentTextureIndex].luafile;
					
					m_entitesForLua.back().pos = position;
					for (auto& etg : m_entityTexGroups)
					{
						if (etg.texturePath == m_entityInstanceTextures[currentTextureIndex].path)
						{
							etg.m_entityPositions.push_back(position);
						}
					}
				}
				

			}

		}
	}


	ImGui::End();
}

void Level::_tileTypePaletteRender()
{
	ImGui::Begin("Tile Type", &m_tileTypePaletteOpen);
	if (_IsClickInside())
	{
		_changeCurrentTool(TOOL_TYPE, "Tile Type", false);
	}

	static std::array<bool,3> selectables = { 1, 0, 0 };
	static int currentType = 0;
	if (ImGui::Selectable("None", &selectables[0]))
	{
		_resetArray(selectables, 0);
		currentType = 0;
	}
	if (ImGui::Selectable("Dangerous", &selectables[1]))
	{
		_resetArray(selectables, 1);
		currentType = 1;
	}
	if (ImGui::Selectable("Solid", &selectables[2]))
	{
		_resetArray(selectables, 2);
		currentType = 2;
	}
	if (m_activeTool[TOOL_TYPE])
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !_IsMouseInside())
		{
			sf::Vector2i mp = sf::Mouse::getPosition(*m_pWindow) - sf::Vector2i(m_camera->getPosition());
			sf::Vector2i index = mp / static_cast<int>(m_grid->getTile(0, 0).getSize().x + 0.5f);

			if (index.x >= 0 && index.y >= 0 && index.x < m_grid->getWidth() && index.y < m_grid->getHeight())
			{

				m_grid->setTypeOfTile(index.x, index.y, currentType);

			}

		}
	}
	

	ImGui::End();
}

void Level::_tileColorPaletteRender()
{
	ImGui::Begin("Colors", &m_tileColorPaletteOpen);
	if (_IsClickInside())
		_changeCurrentTool(TOOL_COLOR, "Tile Colors", true);
	static std::array<float, 4> colors;
	static bool removeSprite = false;
	ImGui::ColorPicker4("Colors", colors.data());
	ImGui::Selectable("Remove Sprite", &removeSprite);
	
	if (m_activeTool[TOOL_COLOR])
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !_IsMouseInside())
		{
			sf::Vector2i mp = sf::Mouse::getPosition(*m_pWindow) - sf::Vector2i(m_camera->getPosition());
			sf::Vector2i index = mp / static_cast<int>(m_grid->getTile(0, 0).getSize().x + 0.5f);

			if (index.x >= 0 && index.y >= 0 && index.x < m_grid->getWidth() && index.y < m_grid->getHeight())
			{
				if (removeSprite)
					m_grid->removeTextureOfTile(index.x, index.y);
				m_grid->setColorOfTile(index.x, index.y,sf::Vector3i(colors[0] * 255,colors[1] * 255,colors[2] * 255), true);

			}

		}
	}
	

	ImGui::End();
}

bool Level::_IsClickInside() const
{
	return ImGui::IsMouseClicked(0) && _IsMouseInside();
}

bool Level::_IsMouseInside() const
{
	ImVec2 k = ImGui::GetWindowPos();
	ImVec2 l = ImGui::GetMousePos();
	ImVec2 s = ImGui::GetWindowSize();

	return l.x > k.x && l.y > k.y && l.x < k.x + s.x && l.y < k.y + s.y;
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
	
	if(NormalMode)	m_grid->NormalMode();
	else m_grid->MarkMode();
}

std::string Level::getTexturePath(std::string luafile) const
{
	std::ifstream luaFile(luafile);
	std::string shaderText((std::istreambuf_iterator<char>(luaFile)), std::istreambuf_iterator<char>());
	luaFile.close();
	int i = shaderText.find("setSprite", 0);
	std::string spritePath = "";
	if (i != -1)
	{
		for (int j = i +11; shaderText[j] != '"'; j++)
			spritePath += shaderText[j];
	}
	return spritePath;
}

void Level::_cleanup()
{

	delete m_grid;
	m_grid = nullptr;
	delete m_camera;
	m_camera = nullptr;

	m_entityTexGroups.clear();
	m_entitesForLua.clear();
	m_entityInstanceTextures.clear();
}

void Level::_copy(const Level & other)
{
	m_grid = new Grid(*other.m_grid);
}
