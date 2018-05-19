#include "Level.hpp" 
#include <fstream> 
#include <sstream> 
#include <iostream> 
#include <filesystem>
#include "imgui.h"
#include "imgui-SFML.h"
#include <array>

#define RUNNING 0
#define WON 1
#define LOSE 2

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
	std::string finalTarget = "Resourses/Levels/" + target;
	m_camera = new Camera(static_cast<float>(0), static_cast<float>(0), m_pWindow->getSize().x, m_pWindow->getSize().y);
	m_loadedSprites = false;
	
	if (target == "")
	{
		m_grid = new Grid(10, 10);
		return;
	}

	std::ifstream map;
	map.open(finalTarget);
	if (map)
	{
		m_currentLevel = target;
		std::cout << target << std::endl;
		m_currentLevel.erase(m_currentLevel.begin() + m_currentLevel.find_last_of('.'), m_currentLevel.end());
		std::string currentLine = "";

		while (std::getline(map, currentLine))
		{
			if (currentLine[0] != '#' && currentLine != "" && currentLine[0] != ' ')
			{
				std::string type = "";
				std::stringstream stream(currentLine);
				stream >> type;
				if (type == "entity")
				{
					std::string spritePath;
					stream >> spritePath;
					std::string luafile;
					stream >> luafile;

					m_entityTexGroups.push_back(EntityTexGroup());
					m_entityTexGroups.back().texturePath = spritePath;
					m_entityTexGroups.back().luafile = luafile;

				}
				else if (type == "p")
				{
					int xCoord, yCoord;
					stream >> xCoord >> yCoord;

					sf::Vector2f pos(xCoord, yCoord);
					
					
					m_entityTexGroups.back().m_entitesForLua.push_back(EntityShape());
					m_entityTexGroups.back().m_entitesForLua.back().shape = sf::RectangleShape(sf::Vector2f(32, 32));
																	// The first entity being loaded is the player
					m_entityTexGroups.back().m_entitesForLua.back().isPlayer = (m_entityTexGroups.size() == 1);
					m_entityTexGroups.back().m_entitesForLua.back().textureObj = new sf::Texture();
					m_entityTexGroups.back().m_entitesForLua.back().textureObj->loadFromFile(m_entityTexGroups.back().texturePath);
					m_entityTexGroups.back().m_entitesForLua.back().shape.setTexture(m_entityTexGroups.back().m_entitesForLua.back().textureObj);
					m_entityTexGroups.back().m_entitesForLua.back().shape.setPosition(pos);
					m_entityTexGroups.back().m_entitesForLua.back().pos = pos;
				
					
				}
				else if (type == "sheet")
				{
					std::string path;
					stream >> path;
					if(path != "")
						m_grid->LoadSpriteSheet(path);
					
							
				}
				else if (type == "t")
				{
					int x, y, t, r, g, b, itx, ity;
					sscanf_s(currentLine.c_str(), "%*s %d %d %d %d %d %d %d %d", &x, &y, &t, &r, &g, &b, &itx, &ity);
					m_grid->setTypeOfTile(x, y, t);
					m_grid->setColorOfTile(x, y, r, g, b);
					float tileSize = m_grid->getTileDim().x;
					if(itx != -1)
						m_grid->setTextureOfTile(x, y, sf::IntRect(itx, ity, tileSize, tileSize));
					// else No spritesheet was present when saving
					
				}		
				else if (type == "grid")
				{
					int w, h, s, t;

					sscanf_s(currentLine.c_str(), "%*s %i %i %i %i", &w, &h, &s, &t);

					if (m_grid)
						delete m_grid;
					m_grid = new Grid(w, h, static_cast<float>(s), t);
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
		int currentIndex = 0;
		for (auto& etg : m_entityTexGroups)
		{
			if (etg.m_entitesForLua.size())
			{
				map << "entity " << etg.texturePath << " " << etg.luafile << "\n";
				for (auto& e : etg.m_entitesForLua)
					map << "p " << e.pos.x << " " << e.pos.y << "\n";
				currentIndex++;
			}
			
		}
		map << m_grid->toFile();
	}

	map.close();

	map.open(luaName);
	// Creating the lua file
	if(map)
	{
		std::vector<sf::Vector2i> goals = m_grid->getGoalTilesPositions();
		int numberOfEntitys = 0;
		for (auto& e : m_entityTexGroups)
		{
			numberOfEntitys += e.m_entitesForLua.size();
		}
		map << "--Auto generated code based on map\n";
		map << "\n";
		map << "local Entities = {}\n";
		map << "\n";
		if (goals.size())
		{
			map << "local GoalTiles = {}\n";
		}
		map << "local function _initEntities()\n";
		for (auto& e : m_entityTexGroups)
		{
			for (auto& ee : e.m_entitesForLua)
			{
				map << "\tlocal Entity_Scripted = Character.Create()\n";
				map << "\tEntity_Scripted:AddScript(\"" << e.luafile << "\")\n";
				map << "\tEntity_Scripted:setPosition(" << ee.pos.x << ","<< ee.pos.y << ")\n";
				map << "\tEntity_Scripted:setSize(" << ee.shape.getSize().x << "," << ee.shape.getSize().y << ")\n";
				map << "\ttable.insert(Entities, Entity_Scripted)\n";
			}
		}
		map << "\n";
		for (auto& g : goals)
		{
			map << "\tlocal Goal = Character.Create()\n";
			map << "\tGoal:setPosition(" << g.x << "," << g.y <<")\n";
			map << "\tGoal:setSize(32,32)\n";
			map << "\ttable.insert(GoalTiles, Goal)\n";
		}
		map << "end\n";
		map << "\n";

		map << "local function _updateEntities()\n";
			map << "\tsetPlayerPosition(Entities[1]:getPosition())\n";
			map << "\tfor i = 1, #Entities, 1 do\n";
				map << "\t\tEntities[i]:Update()\n";
				map << "\t\tmRx, mRy = Entities[i]:getMoveRequest()\n";
				map << "\t\tif mRx ~= 0.0 or mRy ~= 0.0 then\n";
				map << "\t\t\tmx, my = canMove(Entities[i], mRx, mRy)\n";
				map << "\t\t\tif mx == false then\n";
				map << "\t\t\t\t mRx = 0.0 \n";
				map << "\t\t\tend\n";
				map << "\t\t\tif my == false then\n";
				map << "\t\t\t\t mRy = 0.0\n";
				map << "\t\t\tend\n";
				map << "\t\t\tEntities[i]:Move(mRx, mRy)\n";
				map << "\t\tend\n";
				//map << "\t\tend\n";
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
				map << "\t\tisCollision = CheckCollision(Entities[1], Entities[i])\n";
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
		if (goals.size())
		{
			map << "\t\tfor i = 1, #GoalTiles, 1 do\n";
			map << "\t\t\tif CheckCollision(Entities[1], GoalTiles[i]) then\n";
			map << "\t\t\t\tsetGameStatus(" << WON << ")\n";
			map << "\t\t\tend\n";
			map << "\t\tend\n";
		}
		map << "\t\t_updateEntities()\n";
		map << "\t\t_collisionHandling()\n";
		map << "\telse\n";
		map << "\t\tsetGameStatus(" << LOSE << ")\n";
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

const std::vector<std::vector<Tile>>* Level::getMap() const
{
	return m_grid->getTiles();
}

void Level::Update()
{
	m_grid->update(m_camera);
	m_camera->update();
}

void Level::EditorRender()
{	
	for (auto& e : m_entityTexGroups)
	{
		for (auto& ee : e.m_entitesForLua)
		{
			ee.shape.setPosition(ee.pos + m_camera->getPosition());
			m_pWindow->draw(ee.shape);
		}
		
	}

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

void Level::Draw(sf::Vector2f camPos)
{
	m_camera->setPosition(-camPos);
	
	m_pWindow->draw(*m_grid);
	
}

void Level::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	m_pWindow->draw(*m_grid);
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
				m_entityInstanceTextures.clear();
				m_loadedSprites = false;
				
			}


			ImGui::EndMenu();

		}
		if (ImGui::BeginMenu("Open"))
		{
			auto files = filesInDir("Resourses/Levels/");
			
			for (auto& s : files)
			{
				if (ImGui::MenuItem(s.c_str()))
				{
					s.erase(s.begin());
					LoadLevel(s);
				}

			}
			ImGui::EndMenu();
		}
		
		static bool saved = false;
		if (m_currentLevel != "" && ImGui::MenuItem("Save"))
		{
			if (m_entityTexGroups.size())
			{

				saved = SaveLevel(m_currentLevel);			
				if (saved)
					ImGui::BulletText("Saved Succ");
			}
			else
			{
				ImGui::Text("You need to have player present to save!");
			}
	
		}
		else
			saved = false;

		if (ImGui::BeginMenu("Save As.."))
		{
			if (m_entityTexGroups.size())
			{
				static char name[20] = {};

				ImGui::InputText("File path", name, 20);
				if (ImGui::Button("Save"))
				{

					saved = SaveLevel(std::string(name));


				}
				if (saved)
					ImGui::BulletText("Saved Succ");
			}
			else
			{
				ImGui::Text("You need to have player present to save!");
			}

			ImGui::EndMenu();
		}

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

	int tSize = m_grid->getTile(0, 0).getSize().x;

	if (!m_grid->isSpritesheetLoaded())
	{
		auto sprites = filesInDir("Resourses/SpriteSheet");
		static int currentSheetIndex = -1;
		static std::array<bool, 10> selectable{ 0,0,0,0,0,0 };
		for (int i = 0; i < sprites.size(); i++)
		{
			if (ImGui::Selectable(sprites[i].c_str(), &selectable[i]))
			{
				_resetArray(selectable, i);
				currentSheetIndex = i;
			}

		}

		if (currentSheetIndex != -1 && ImGui::Button("Load"))
		{

			std::string fullPath = "Resourses/SpriteSheet/";
			fullPath += std::string(sprites[currentSheetIndex]);

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

		if (ImGui::Button("New Sheet"))
		{

			m_grid->UnloadSpriteSheet();

		}

		if (ImGui::Button("Fill With Selected Sprite"))
		{

			m_grid->setTextureOfAllTiles(rect);
			
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
	static std::vector<std::string> ent;
	static std::string playerFolderPath = "Scripts/Player";
	static std::vector<std::string> pla;
	
	static int currentTextureIndex = -1;
	
	if (!m_loadedSprites)
	{
		ent = filesInDir(path);
		pla = filesInDir(playerFolderPath);

		m_sampleTexture.loadFromFile("sample.png");
		m_displayTexure.setTexture(m_sampleTexture);


		auto ip = std::begin(pla);
		while (ip != std::end(pla))
		{
			std::string currentPath;

			currentPath += playerFolderPath + (*ip).c_str();
			std::string yes = getTexturePath(currentPath);

			if (yes == "")
			{
				ip = pla.erase(ip);
			}
			else
			{
				m_entityInstanceTextures.push_back(TextureWPath());
				m_entityInstanceTextures.back().texture.loadFromFile(yes);
				m_entityInstanceTextures.back().path = yes;
				if ((*ip)[0] == '\\')
					(*ip).erase((*ip).begin());
				std::string luaPath = "Scripts/Player/" + *ip;
				m_entityInstanceTextures.back().luafile = luaPath;
				ip++;
			}

		}

		auto i = std::begin(ent);
		while (i != std::end(ent))
		{
			std::string currentPath;

			currentPath += path + (*i).c_str();
			std::string yes = getTexturePath(currentPath);
			
			if (yes == "")
			{
				i = ent.erase(i);
			}
			else
			{
				
					m_entityInstanceTextures.push_back(TextureWPath());
					m_entityInstanceTextures.back().texture.loadFromFile(yes);
					m_entityInstanceTextures.back().path = yes;
					if ((*i)[0] == '\\')
						(*i).erase((*i).begin());
					std::string luaPath = "Scripts/" + *i;
					m_entityInstanceTextures.back().luafile = luaPath;
				
				
				
				i++;
			}

		}
		
		m_loadedSprites = true;

	}
	
	ImGui::Image(m_displayTexure);
	ImGui::TextColored(ImVec4(0,255,0,255),"Player Entities");
	ImGui::Separator();
	static std::array<bool, 10> selectable{ 0,0,0,0,0,0 };
	int textureIndex = 0;
	for (int i = 0; i < pla.size(); i++)
	{
		if (ImGui::Selectable(pla[i].c_str(), &selectable[textureIndex]))
		{
			_resetArray(selectable, textureIndex);
			currentTextureIndex = textureIndex;
			m_displayTexure.setTexture(m_entityInstanceTextures[textureIndex].texture);
		}
		textureIndex++;

	}

	ImGui::Separator();
	ImGui::TextColored(ImVec4(255, 0, 0, 255), "Entites");
	ImGui::Separator();
	for (int i = 0; i < ent.size(); i++)
	{
		if (ImGui::Selectable(ent[i].c_str(), &selectable[textureIndex]))
		{
			_resetArray(selectable, textureIndex);
			currentTextureIndex = textureIndex;

			m_displayTexure.setTexture(m_entityInstanceTextures[textureIndex].texture);
		}
		textureIndex++;

	}

	if (m_activeTool[TOOL_ENTITY] && currentTextureIndex != -1)
	{
		bool placeMode = sf::Mouse::isButtonPressed(sf::Mouse::Left);
		bool deleteMode = sf::Mouse::isButtonPressed(sf::Mouse::Right);
		if ((placeMode || deleteMode) && !_IsMouseInside())
		{
			sf::Vector2i mp = sf::Mouse::getPosition(*m_pWindow) - sf::Vector2i(m_camera->getPosition());
			sf::Vector2i index = mp / static_cast<int>(m_grid->getTile(0, 0).getSize().x + 0.5f);

			if (index.x >= 0 && index.y >= 0 && index.x < m_grid->getWidth() && index.y < m_grid->getHeight())
			{
				sf::Vector2f position = sf::Vector2f(index.x << 5, index.y << 5);

				bool existing = false;
				for (auto& tg : m_entityTexGroups)
				{
					for (auto& entity : tg.m_entitesForLua)
						if (entity.pos == position)
						{
							existing = true;
							break;
						}

				}

				if (!existing && placeMode)
				{
					// Now are we moving a player 
					if (currentTextureIndex < pla.size())
					{
						bool found = false;
						for (auto& tg : m_entityTexGroups)
						{
							for (auto& e : tg.m_entitesForLua)
							{
								if (e.isPlayer)
								{
									found = true;
									e.pos = position;
									e.shape.setPosition(position + m_camera->getPosition());
									e.shape.setTexture(&m_entityInstanceTextures[currentTextureIndex].texture);
									tg.luafile = m_entityInstanceTextures[currentTextureIndex].luafile;
									tg.texturePath = m_entityInstanceTextures[currentTextureIndex].path;
								}
							}
						}
						// We didnt found an existing player!!
						if (!found)
						{
							EntityTexGroup etg;
							etg.m_entitesForLua.push_back(EntityShape());
							etg.m_entitesForLua.back().shape = sf::RectangleShape(sf::Vector2f(32, 32));
							etg.m_entitesForLua.back().shape.setTexture(&m_entityInstanceTextures[currentTextureIndex].texture);
							etg.m_entitesForLua.back().shape.setPosition(position + m_camera->getPosition());
							etg.m_entitesForLua.back().pos = position;
							etg.m_entitesForLua.back().isPlayer = true;

							etg.luafile = m_entityInstanceTextures[currentTextureIndex].luafile;
							etg.texturePath = m_entityInstanceTextures[currentTextureIndex].path;
							m_entityTexGroups.insert(m_entityTexGroups.begin(), etg);
						}
					}
					else // Now are we placing an entity
					{
						// if the entityTexGroup is empty, we need to create a slot for the player at the begining
						if (!m_entityTexGroups.size())
						{
							EntityTexGroup etg;
							etg.texturePath = "null";
							EntityShape es;
							es.isPlayer = true;
							etg.m_entitesForLua.push_back(es);
							m_entityTexGroups.push_back(etg);
						}
						bool findExisintGroup = false;
						for (auto& tg : m_entityTexGroups)
						{
							if (tg.texturePath == m_entityInstanceTextures[currentTextureIndex].path)
							{
								findExisintGroup = true;
								tg.m_entitesForLua.push_back(EntityShape());
								tg.m_entitesForLua.back().shape = sf::RectangleShape(sf::Vector2f(32, 32));
								tg.m_entitesForLua.back().shape.setTexture(&m_entityInstanceTextures[currentTextureIndex].texture);
								tg.m_entitesForLua.back().shape.setPosition(position + m_camera->getPosition());
								tg.m_entitesForLua.back().pos = position;
								tg.m_entitesForLua.back().isPlayer = false;

								tg.luafile = m_entityInstanceTextures[currentTextureIndex].luafile;
								tg.texturePath = m_entityInstanceTextures[currentTextureIndex].path;
								break;

							}
						}
						if (!findExisintGroup)
						{
							EntityTexGroup etg;
							etg.texturePath = m_entityInstanceTextures[currentTextureIndex].path;
							etg.luafile = m_entityInstanceTextures[currentTextureIndex].luafile;
								EntityShape es;
								es.shape = sf::RectangleShape(sf::Vector2f(32, 32));
								es.shape.setTexture(&m_entityInstanceTextures[currentTextureIndex].texture);
								es.shape.setPosition(position + m_camera->getPosition());
								es.pos = position;
								es.isPlayer = false;
							etg.m_entitesForLua.push_back(es);
							m_entityTexGroups.push_back(etg);
							
						}
					}

					
				}
				else if (deleteMode)
				{
					for (auto& tg : m_entityTexGroups)
					{
						for (int entityIndex = 0; entityIndex < tg.m_entitesForLua.size(); entityIndex++)
						{
							if (tg.m_entitesForLua[entityIndex].pos.x == index.x << 5 && tg.m_entitesForLua[entityIndex].pos.y == index.y << 5)
							{
								if(!tg.m_entitesForLua[entityIndex].isPlayer)
									tg.m_entitesForLua.erase(tg.m_entitesForLua.begin() + entityIndex);
								break;
							}

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

	static std::array<bool,4> selectables = { 1, 0, 0 , 1};
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
	if (ImGui::Selectable("Goal", &selectables[3]))
	{
		_resetArray(selectables, 3);
		currentType = 3;
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
	if (ImGui::Button("Paint all"))
	{
		m_grid->setColorOfAllTiles(sf::Color(colors[0] * 255, colors[1] * 255, colors[2] * 255), removeSprite);
	}
	
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
	
	m_grid->MarkTiles(!NormalMode);
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
	if(m_entityTexGroups.size())
		delete m_entityTexGroups.front().m_entitesForLua.front().textureObj;

	/*for (auto& etg : m_entityTexGroups)
	{
		for (auto& e : etg.m_entitesForLua)
		{
			delete e.textureObj;
			e.textureObj = nullptr;
			break;
		}
	}*/
	m_entityInstanceTextures.clear();
	m_entityTexGroups.clear();
}

void Level::_copy(const Level & other)
{
	m_grid = new Grid(*other.m_grid);
}
