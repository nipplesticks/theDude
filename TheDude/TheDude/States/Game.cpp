#include "Game.hpp"
#include "../RenderQueue.hpp"


std::vector<Entity*> Render::g_renderQueue;
bool Game::s_isGameRunning = true;
int Game::s_gameStatus = RUNNING;

Game::Game(std::string level) : m_level(s_window)
{
	s_isGameRunning = true; 
	s_gameStatus = RUNNING;

	_init(level);
}

Game::~Game()
{
	delete m_entityHandler;
}

void Game::Update()
{
	if (s_gameStatus == WON)
	{
		m_drawWinText = true; 
	}
	else if(s_gameStatus == LOSE)
	{
		m_drawLoseText = true; 
	}
	
	if (s_isGameRunning)
	{
		m_level.Update();
		m_entityHandler->Update();
	}
	else
	{
		State::Pop();
	}
	
}

void Game::Draw()
{
	
	m_entityHandler->Draw();

	// TEMP
	
	sf::Vector2f m(s_window->getSize());
	m *= 0.5f;
	
	sf::Vector2f camPos(Render::g_renderQueue[0]->getPosition());
	camPos -= m;
	m_level.Draw(camPos);
	for (auto & entity : Render::g_renderQueue)
	{
		sf::Vector2f worldPos = entity->getPosition();
		entity->setViewPos(worldPos - camPos);
		s_window->draw(entity->getShape());
		Character * p = dynamic_cast<Character*>(entity);
		if (p) p->DrawOther(s_window, camPos);
	}

	
	if (m_drawWinText)
	{
		s_window->draw(m_winText);
	}
	else if (m_drawLoseText)
	{
		s_window->draw(m_loseText);
	}
}


void Game::_init(std::string level)
{
	_initEntityHandler("Scripts/" + level + ".lua");
	m_level.LoadLevel(level + ".level"); 
	
	m_winText.setFont("Resourses/FONT/Hollywood Capital Hills (Final).ttf", "YOU WIN!", sf::Vector2f((s_window->getSize().x / 2) - 60,200), 50); 
	m_loseText.setFont("Resourses/FONT/Hollywood Capital Hills (Final).ttf", "YOU LOSE!", sf::Vector2f((s_window->getSize().x / 2) - 60, 200), 50);
	m_drawWinText = false;
	m_drawLoseText = false;
}

void Game::_initEntityHandler(std::string luaFile)
{
	m_entityHandler = new OurLua(luaFile);
	_pushFunctions();
	m_entityHandler->InitLua();
}


void Game::_pushFunctions()
{
	m_entityHandler->PushFunction(s_CheckCollision, "CheckCollision");
	m_entityHandler->PushFunction(s_GetMousePos, "getMousePos");

	m_entityHandler->PushFunction(s_isKeyPressed, "isKeyPressed");
	m_entityHandler->PushFunction(s_ExitGame, "ExitGame");
	m_entityHandler->PushFunction(s_setPlayerPos, "setPlayerPosition");
	m_entityHandler->PushFunction(s_mapCol, "canMove");
	m_entityHandler->PushFunction(s_setGameStatus, "setGameStatus");

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
		{ "getProjectiles"		,Character::s_getProjectiles		},
		{ "__gc"				,Character::s_Destroy				},
		{ NULL					,NULL								}
	};
	m_entityHandler->PushClassFunctions(Character::metaTable, characterFunctions, "Character");

	luaL_Reg bulletFunctions[]
	{
	{ "getDamage"			,Projectile::s_getDamage },
	{ "Disable"				,Projectile::s_DisableAndDelete },
	{ NULL					,NULL }
	};
	m_entityHandler->PushClassFunctions(Projectile::metaTable, bulletFunctions, "Projectile");

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
		else if (!_strcmpi(key.c_str(), "lmouse"))
			s[0] = sf::Mouse::isButtonPressed(sf::Mouse::Left);
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

int Game::s_GetMousePos(lua_State * l)
{
	std::vector<int> mousePos;
	sf::Vector2i ms = sf::Mouse::getPosition(*s_window);
	sf::Vector2u ws = s_window->getSize();
	ms.x -= ws.x / 2;
	ms.y -= ws.y / 2;
	mousePos.push_back(ms.x);
	mousePos.push_back(ms.y);

	OurLua::setIntegers(l, mousePos);

	return 2;
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
#define NONE 0
#define SOLID 1
#define DANGEROUS 2
	auto map = Hack::g->m_level.getMap();
	int mx = NONE;
	int my = NONE;
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
			mx = SOLID;
		}
		else if((*map)[x1.x / tSize][x1.y / tSize].getType() == Tile::Dangerous||
				(*map)[x2.x / tSize][x2.y / tSize].getType() == Tile::Dangerous)
			{
				mx = DANGEROUS;
			}

		if (dir.y)
		{
			if ((*map)[y1.x / tSize][y1.y / tSize].getType() == Tile::Solid ||
				(*map)[y2.x / tSize][y2.y / tSize].getType() == Tile::Solid)
			{
				my = SOLID;
			}
			else if ((*map)[y1.x / tSize][y1.y / tSize].getType() == Tile::Dangerous ||
				(*map)[y2.x / tSize][y2.y / tSize].getType() == Tile::Dangerous)
			{
				my = DANGEROUS;
			}
		}
	}

	std::vector<int> colVec;
	colVec.push_back(mx);
	colVec.push_back(my);
	OurLua::setIntegers(l, colVec);
	
	return 2;
}

int Game::s_setGameStatus(lua_State * l)
{
	std::vector<float> status = OurLua::getFloats(l, 1);
	Game::s_gameStatus = status[0];
	return 0;
}
