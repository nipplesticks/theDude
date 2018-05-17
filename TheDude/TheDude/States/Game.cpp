#include "Game.hpp"
#include "../RenderQueue.hpp"

std::vector<Entity*> Render::g_renderQueue;
bool Game::s_isGameRunning = true;

Game::Game()
{
	m_entityHandler = nullptr;
	p_wnd = nullptr;
	m_collisionArr = new bool*[100];
	for (int i = 0; i < 100; i++)
	{
		m_collisionArr[i] = new bool[100]; 
		for (int k = 0; k < 100; k++)
		{
			m_collisionArr[i][k] = false;
		}
	}
	m_collisionArr[0][0] = true;
	rectArr[0] = { 0,0,32,32 }; 
	m_collisionArr[10][10] = true;
	rectArr[1] = { 10,10,32,32 };
	m_collisionArr[20][20] = true;
	rectArr[2] = { 20,20,32,32 };
	m_collisionArr[30][30] = true;
	rectArr[3] = { 30,30,32,32 };
	m_collisionArr[40][40] = true;
	rectArr[4] = { 40,40,32,32 };
}

Game::~Game()
{
	delete m_entityHandler;
	for (int i = 0; i < 100; i++)
	{
		delete[] m_collisionArr[i]; 
	}
	delete[] m_collisionArr; 
}

bool ** Game::getCollisionArr()
{
	return m_collisionArr;
}

void Game::Init(sf::RenderWindow * wnd)
{
	p_wnd = wnd;
	_init();
}

void Game::update()
{
	if (s_isGameRunning)
	{
		m_entityHandler->Update(); 
	}
	else
	{
		p_wnd->close();
	}
}

void Game::draw()
{
	m_entityHandler->Draw();


	// TEMP
	sf::Vector2f camPos(0.0f, 0.0f);

	for (auto & entity : Render::g_renderQueue)
	{
		sf::Vector2f worldPos = entity->getPosition();
		entity->setViewPos(worldPos - camPos);
		p_wnd->draw(entity->getShape());
	}
	p_wnd->display();
}

void Game::_init()
{
	_initEntityHandler();
}

void Game::_initEntityHandler()
{
	m_entityHandler = new OurLua("Scripts/EntityHandler.Lua");
	m_entityHandler->PushClassFunction(this, Game::s_mapCol, "testMe");
	_pushFunctions();
	m_entityHandler->InitLua();
}

void Game::_pushFunctions()
{
	m_entityHandler->PushFunction(s_CheckCollision,	"CheckCollision");
	m_entityHandler->PushFunction(s_isKeyPressed,	"isKeyPressed");
	m_entityHandler->PushFunction(s_ExitGame,		"ExitGame");
	m_entityHandler->PushFunction(s_setPlayerPos,	"setPlayerPosition");

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

int Game::s_mapCol(lua_State * l)
{
	auto gamePtr = OurLua::getClassPointer<Game>(l);
	std::vector<Entity**> e = OurLua::getInstancePointer<Entity>(l,1);
	bool** map = gamePtr->getCollisionArr(); 
	bool collided = false;
	sf::IntRect collidePoints[8]; 

	for (int i = 0; i < e.size() && !collided; i++)
	{
		int eTileX = (*e[i])->getPosition().x / 32; 
		int eTileY = (*e[i])->getPosition().y / 32; 

		sf::Vector2i generalSize = sf::Vector2i((*e[i])->getShape().getSize()); 
		//Set collidePoints 
		
		//LeftUp
		collidePoints[0] = sf::IntRect{ int((*e[i])->getPosition().x) + 2, int((*e[i])->getPosition().y) + 2,3,3};
		//LeftDown
		collidePoints[1] = sf::IntRect{ int((*e[i])->getPosition().x) + 2, int((*e[i])->getPosition().y) + (generalSize.y - 4),3,3 };
		//UpLeft
		collidePoints[2] = sf::IntRect{ int((*e[i])->getPosition().x) + 4, int((*e[i])->getPosition().y) + 1,3,3 };
		//UpRight 
		collidePoints[3] = sf::IntRect{ int((*e[i])->getPosition().x) + (generalSize.x - 4), int((*e[i])->getPosition().y) + 1,3,3 };
		//RightUp
		collidePoints[4] = sf::IntRect{ int((*e[i])->getPosition().x) + (generalSize.x - 2), int((*e[i])->getPosition().y) + 2,3,3 };
		//RightDown
		collidePoints[5] = sf::IntRect{ int((*e[i])->getPosition().x) + (generalSize.x - 2), int((*e[i])->getPosition().y) + (generalSize.y - 4),3,3 };
		//DownLeft
		collidePoints[6] = sf::IntRect{ int((*e[i])->getPosition().x) + 4, int((*e[i])->getPosition().y) + (generalSize.y - 2),3,3 };
		//DownRight
		collidePoints[7] = sf::IntRect{ int((*e[i])->getPosition().x) +	(generalSize.x - 4), int((*e[i])->getPosition().y) + (generalSize.y - 2),3,3 };

		std::cout<< "\rT(" << eTileX << "," << eTileY << ")" << " P(" << (*e[i])->getPosition().x << ", " << (*e[i])->getPosition().y << ")" <<std::flush;
		
		if (eTileX > 0 && eTileY > 0 &&
			eTileX < 38 && eTileY < 40)
		{
			//Right
			if (map[eTileX + 1][eTileY] == true)
			{
				sf::IntRect lol = { int((*e[i])->getPosition().x + 32) ,int((*e[i])->getPosition().y),32,32 };
				if (lol.intersects(collidePoints[4]) ||lol.intersects(collidePoints[5]))
				{ 
					collided = true; 
				}
			}
			//Left
			  if (map[eTileX - 1][eTileY] == true)
			{
				sf::IntRect lol = { int((*e[i])->getPosition().x - generalSize.x) ,int((*e[i])->getPosition().y),generalSize.x,generalSize.y };
				if (lol.intersects(collidePoints[0]) || lol.intersects(collidePoints[1]))
					collided = true; 
			}
			//Up
			  if (map[eTileX][eTileY - 1] == true)
			{
				sf::IntRect lol = { int((*e[i])->getPosition().x) , int((*e[i])->getPosition().y) - generalSize.y,generalSize.x,generalSize.y };
				if (lol.intersects(collidePoints[2]) || lol.intersects(collidePoints[3]))
					collided = true;
			}
			//Down
			  if (map[eTileX][eTileY + 1] == true)
			{
				sf::IntRect lol = {int((*e[i])->getPosition().x),int((*e[i])->getPosition().y) + generalSize.y ,generalSize.x,generalSize.y};
				if (lol.intersects(collidePoints[6]) || lol.intersects(collidePoints[7])) 
					collided = true;
			}
		}
	}
		
	std::vector<bool> colVec;
	colVec.push_back(collided);
	OurLua::setBooleans(l, colVec);

	return 1;
}
