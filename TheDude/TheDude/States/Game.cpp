#include "Game.hpp"
#include "../RenderQueue.hpp"

std::vector<Entity*> Render::g_renderQueue;
bool Game::s_isGameRunning = true;

Game::Game() : m_level(s_window)
{
	s_isGameRunning = true;
	_init();
}

Game::~Game()
{
	delete m_entityHandler;
	
}



void Game::Update()
{
	if (s_isGameRunning)
	{
		m_entityHandler->Update();
		m_level.Update(); 
	}
	else
	{
		State::Pop();
	}
}

void Game::Draw()
{
	s_window->draw(m_level); 
	m_entityHandler->Draw();

	// TEMP
	sf::Vector2f camPos(0.0f, 0.0f);

	for (auto & entity : Render::g_renderQueue)
	{
		sf::Vector2f worldPos = entity->getPosition();
		s_window->draw(entity->getShape());
		entity->setViewPos(worldPos - camPos);
		Character * p = dynamic_cast<Character*>(entity);
		if (p) p->DrawOther(s_window);
	}
}


void Game::_init()
{
	_initEntityHandler();
	m_level.LoadLevel("Resourses/Levels/game.level"); 
}

void Game::_initEntityHandler()
{
	m_entityHandler = new OurLua("Scripts/game.lua");
	_pushFunctions();
	m_entityHandler->InitLua();
}

void Game::_pushFunctions()
{
	m_entityHandler->PushFunction(s_CheckCollision, "CheckCollision");
	m_entityHandler->PushFunction(s_isKeyPressed, "isKeyPressed");
	m_entityHandler->PushFunction(s_ExitGame, "ExitGame");
	m_entityHandler->PushFunction(s_setPlayerPos, "setPlayerPosition");
	m_entityHandler->PushFunction(s_mapCol, "canMove");

	luaL_Reg characterFunctions[]
	{
		{ "Create"				,Character::s_Create				},
		{ "setColor"			,Character::s_setColor				},
		{ "setPosition"			,Character::s_setPosition			},
		{ "Move"				,Character::s_Move					},
		{ "setSize"				,Character::s_setSize				},
		{ "setOrigin"			,Character::s_setOrigin				},
		{ "getPosition"			,Character::s_getPosition			},
		{ "getSize"				,Character::s_getSize				},
		{ "getColor"			,Character::s_getColor				},
		{ "Draw"				,Character::s_Draw					},
		{ "AddScript"			,Character::s_AddScript				},
		{ "isDead"				,Character::s_isDead				},
		{ "setHealth"			,Character::s_setHealth				},
		{ "setAttack"			,Character::s_setAttack				},
		{ "setDefence"			,Character::s_setDefence			},
		{ "AlterHealth"			,Character::s_AlterHealth			},
		{ "getHealth"			,Character::s_getHealth				},
		{ "getAttack"			,Character::s_getAttack				},
		{ "getDefence"			,Character::s_getDefence			},
		{ "Update"				,Character::s_Update				},
		{ "setSprite"			,Character::s_SetSprite				},
		{ "getDistanceToPlayer"	,Character::s_getDistanceToPlayer	},
		{ "MoveRequest"			,Character::s_MoveRequest			},
		{ "getMoveRequest"		,Character::s_getMoveRequest		},
		{ "__gc"				,Character::s_Destroy				},
		{ NULL					,NULL								}
	};
	m_entityHandler->PushClassFunctions(Character::metaTable, characterFunctions, "Character");
}
int Game::s_isKeyPressed(lua_State * l)
{
	std::string key = OurLua::getStrings(l, 1)[0];
	std::vector<bool> s;
	s.push_back(false);

	if (key.size() > 1)
	{
		if (!_strcmpi(key.c_str(), "esc"))
			s[0] = GetAsyncKeyState(VK_ESCAPE);
		else if (!_strcmpi(key.c_str(), "space"))
			s[0] = GetAsyncKeyState(VK_SPACE);
		else if (!_strcmpi(key.c_str(), "lshift"))
			s[0] = GetAsyncKeyState(VK_LSHIFT);
		else if (!_strcmpi(key.c_str(), "up"))
			s[0] = GetAsyncKeyState(VK_UP);
		else if (!_strcmpi(key.c_str(), "down"))
			s[0] = GetAsyncKeyState(VK_DOWN);
		else if (!_strcmpi(key.c_str(), "right"))
			s[0] = GetAsyncKeyState(VK_RIGHT);
		else if (!_strcmpi(key.c_str(), "left"))
			s[0] = GetAsyncKeyState(VK_LEFT);
	}
	else if (GetAsyncKeyState(static_cast<int>(key[0])))
	{
		s[0] = true;
	}
	OurLua::setBooleans(l, s);
	return 1;
}

int Game::s_CheckCollision(lua_State * l)
{
	std::vector<Entity**> e = OurLua::getInstancePointer<Entity>(l, 2);
	std::vector<bool> col;
	col.push_back(false);
	sf::Vector2f p0, p1, s0, s1;
	p0 = (*e[0])->getPosition();
	p1 = (*e[1])->getPosition();
	s0 = (*e[0])->getSize();
	s1 = (*e[1])->getSize();

	if (!(p1.x > p0.x + s0.x
		|| p1.x + s1.x < p0.x
		|| p1.y > p0.y + s0.y
		|| p1.y + s1.y < p0.y))
	{
		col[0] = true;
	}

	OurLua::setBooleans(l, col);
	return 1;
}

int Game::s_ExitGame(lua_State * l)
{
	Game::s_isGameRunning = false;
	return 0;
}

int Game::s_setPlayerPos(lua_State * l)
{
	std::vector<float> position = OurLua::getFloats(l, 2);
	Character::playerPos.x = position[1];
	Character::playerPos.y = position[0];

	return 0;
}
#include "../Hack.hpp"
int Game::s_mapCol(lua_State * l)
{
	auto d = OurLua::getFloats(l, 2);
	Entity * e = (*OurLua::getInstancePointer<Entity>(l, 1)[0]);
	sf::Vector2f dir(d[1], d[0]);

	auto map = Hack::g->m_level.getMap();
	bool mx = true;
	bool my = true;
	sf::FloatRect collidePoints[4]; 
	int tSize = (*map)[0][0].getSize().x;
	sf::Vector2f generalSize = sf::Vector2f(e->getShape().getSize());

	int eTileX = e->getPosition().x / tSize;
	int eTileY = e->getPosition().y / tSize;
 
	float lol1, lol2, lol3, lol4;
	lol1 = (e->getPosition().x + dir.x) / tSize;
	lol2 = (e->getPosition().y + dir.y) / tSize;
	lol3 = (e->getPosition().x + dir.x + e->getSize().x) / tSize;
	lol4 = (e->getPosition().y + dir.y + e->getSize().y) / tSize;

	//Set collidePoints 
	
	float realPosX = e->getPosition().x;
	float realPosY = e->getPosition().y;

	int pointSize = 1; 

	if (lol1 > 0.0 && lol1 < map->size() &&
		lol3 > 0.0 && lol3 < map->size() &&
		lol2 > 0.0 && lol2 < map->at(0).size() &&
		lol4 > 0.0 && lol4 < map->at(0).size())
	{
		sf::Vector2f x1;
		sf::Vector2f x2;
		sf::Vector2f y1;
		sf::Vector2f y2;

		if (dir.x < 0)
		{
			x1.x = realPosX + dir.x;
			x1.y = realPosY - dir.x + 0.5f;

			x2.x = realPosX + dir.x;
			x2.y = realPosY + generalSize.y + dir.x - 0.5f;
		}
		else
		{
			x1.x = realPosX + dir.x + generalSize.x;
			x1.y = realPosY + dir.x + 0.5f;

			x2.x = realPosX + dir.x + generalSize.x;
			x2.y = realPosY + generalSize.y - dir.x - 0.5f;
		}

		if (dir.y < 0)
		{
			y1.x = realPosX - dir.y + 0.5f;
			y1.y = realPosY + dir.y;

			y2.x = realPosX + generalSize.x + dir.y - 0.5f;
			y2.y = realPosY + dir.y;
		}
		else
		{
			y1.x = realPosX + dir.y + 0.5f;
			y1.y = realPosY + generalSize.y + dir.y;

			y2.x = realPosX + generalSize.x - dir.y - 0.5f;
			y2.y = realPosY + generalSize.y + dir.y;
		}


		if ((*map)[x1.x / tSize][x1.y / tSize].getType() == Tile::Solid ||
			(*map)[x2.x / tSize][x2.y / tSize].getType() == Tile::Solid)
		{
			mx = false;
		}

		if (dir.y)
		{
			if ((*map)[y1.x / tSize][y1.y / tSize].getType() == Tile::Solid ||
				(*map)[y2.x / tSize][y2.y / tSize].getType() == Tile::Solid)
			{
				my = false;
			}
		}
	}

	std::vector<bool> colVec;
	colVec.push_back(mx);
	colVec.push_back(my);
	OurLua::setBooleans(l, colVec);
	
	return 2;

	//RightUp			   
	/*collidePoints[4] = sf::FloatRect{ (realPosX) + (generalSize.x - 3), (realPosY) + 4,(float)pointSize,(float)pointSize};
	//RightDown			
	collidePoints[5] = sf::FloatRect{ (realPosX) + (generalSize.x - 3), (realPosY) + (generalSize.y - 4),(float)pointSize,(float)pointSize};
	//DownLeft
	collidePoints[6] = sf::FloatRect{ (realPosX) + 4, (realPosY) + (generalSize.y - 3),(float)pointSize,(float)pointSize};
	//DownRight		
	collidePoints[7] = sf::FloatRect{ (realPosX) + (generalSize.x - 4), (realPosY) + (generalSize.y - 3),(float)pointSize, (float)pointSize};


	//Makes sure the points collision check is calculated from the middle of every point
	sf::Vector2f PointPosLeftUp = sf::Vector2f{collidePoints[0].left, collidePoints[0].top};
	sf::Vector2f PointPosLeftDown = sf::Vector2f{ collidePoints[1].left, collidePoints[1].top};
	sf::Vector2f PointPosUpLeft = sf::Vector2f{ collidePoints[2].left + ((float)pointSize / 2), collidePoints[2].top};
	sf::Vector2f PointPosUpRight = sf::Vector2f{ collidePoints[3].left + ((float)pointSize / 2), collidePoints[3].top};
	sf::Vector2f PointPosRightUp = sf::Vector2f{ collidePoints[4].left + (float)pointSize, collidePoints[4].top};
	sf::Vector2f PointPosRightDown = sf::Vector2f{ collidePoints[5].left + (float)pointSize, collidePoints[5].top};
	sf::Vector2f PointPosDownLeft = sf::Vector2f{ collidePoints[6].left + ((float)pointSize / 2), collidePoints[6].top + (float)pointSize };
	sf::Vector2f PointPosDownRight = sf::Vector2f{ collidePoints[7].left + ((float)pointSize / 2), collidePoints[7].top + (float)pointSize};

	std::cout<< "\rT(" << eTileX << "," << eTileY << ")" << " P(" << realPosX << ", " << realPosY << ")" <<std::flush;

	if (eTileX > 0 && eTileY > 0 &&
		eTileX < map->size() - 1&& eTileY < map[0].size() - 1)
	{
		//Left
		if ((*map)[(int)(PointPosLeftUp.x + 0.5f) / tSize][(int)(PointPosLeftUp.y + 0.5f) / tSize].getType() == Tile::Solid ||
			(*map)[(int)(PointPosLeftDown.x + 0.5f) / tSize][(int)(PointPosLeftDown.y + 0.5f) / tSize].getType() == Tile::Solid)
		{
			mx = false; 
		}
		//Right
		if ((*map)[PointPosRightUp.x / tSize][PointPosRightUp.y / tSize].getType() == Tile::Solid ||
			(*map)[PointPosRightDown.x / tSize][PointPosRightDown.y / tSize].getType() == Tile::Solid)
		{
			mx = false; 
		}
		//Up
			if ((*map)[PointPosUpLeft.x / tSize][PointPosUpLeft.y / tSize].getType() == Tile::Solid ||
				(*map)[PointPosUpRight.x / tSize][PointPosUpRight.y / tSize].getType() == Tile::Solid)
		{
				my = false;
		}
		//Down
			if ((*map)[PointPosDownLeft.x / tSize][PointPosDownLeft.y / tSize].getType() == Tile::Solid ||
				(*map)[PointPosDownRight.x / tSize][PointPosDownRight.y / tSize].getType() == Tile::Solid)
		{
				my = false;
		}
	}
	
	std::vector<bool> colVec;
	colVec.push_back(mx);
	colVec.push_back(my); 
	OurLua::setBooleans(l, colVec);
	return 2;
	*/
}
