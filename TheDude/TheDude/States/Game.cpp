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
	m_entityHandler = new OurLua("Scripts/game.Lua");
	_pushFunctions();
	m_entityHandler->InitLua();
}

void Game::_pushFunctions()
{
	m_entityHandler->PushFunction(s_CheckCollision, "CheckCollision");
	m_entityHandler->PushFunction(s_isKeyPressed, "isKeyPressed");
	m_entityHandler->PushFunction(s_ExitGame, "ExitGame");
	m_entityHandler->PushFunction(s_setPlayerPos, "setPlayerPosition");

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
	//auto gamePtr = OurLua::getClassPointer<Game>(l);
	
	//std::vector<Entity**> e = OurLua::getInstancePointer<Entity>(l,1);
	auto e = OurLua::getClassPointer<Entity>(l);
	auto map = Hack::g->m_level.getMap();
	bool collided = false;
	sf::IntRect collidePoints[8]; 
	int tSize = (*map)[0][0].getSize().x;
	int eTileX = e->getPosition().x / tSize; 
	int eTileY = e->getPosition().y / tSize; 

	sf::Vector2i generalSize = sf::Vector2i(e->getShape().getSize()); 
	//Set collidePoints 
	
	int pointSize = 3; 

	//LeftUp
	collidePoints[0] = sf::IntRect{ int(e->getPosition().x) + 2, int(e->getPosition().y) + 2,pointSize,pointSize };
	//LeftDown
	collidePoints[1] = sf::IntRect{ int(e->getPosition().x) + 2, int(e->getPosition().y) + (generalSize.y - 4),pointSize,pointSize };
	//UpLeft
	collidePoints[2] = sf::IntRect{ int(e->getPosition().x) + 4, int(e->getPosition().y) + 1,pointSize,pointSize };
	//UpRight 
	collidePoints[3] = sf::IntRect{ int(e->getPosition().x) + (generalSize.x - 4), int(e->getPosition().y) + 1,pointSize,pointSize };
	//RightUp
	collidePoints[4] = sf::IntRect{ int(e->getPosition().x) + (generalSize.x - 2), int(e->getPosition().y) + 2,pointSize,pointSize };
	//RightDown
	collidePoints[5] = sf::IntRect{ int(e->getPosition().x) + (generalSize.x - 2), int(e->getPosition().y) + (generalSize.y - 4),pointSize,pointSize };
	//DownLeft
	collidePoints[6] = sf::IntRect{ int(e->getPosition().x) + 4, int(e->getPosition().y) + (generalSize.y - 2),pointSize,pointSize };
	//DownRight
	collidePoints[7] = sf::IntRect{ int(e->getPosition().x) +	(generalSize.x - 4), int(e->getPosition().y) + (generalSize.y - 2),pointSize,pointSize };

	std::cout<< "\rT(" << eTileX << "," << eTileY << ")" << " P(" << e->getPosition().x << ", " << e->getPosition().y << ")" <<std::flush;

	if (eTileX > 0 && eTileY > 0 &&
		eTileX < map->size() && eTileY < map[0].size())
	{
		//Right
		if ((*map)[eTileX + 1][eTileY].getType() == Tile::Solid)
		{
			sf::IntRect lol = { int(e->getPosition().x + generalSize.x) ,int(e->getPosition().y),generalSize.x,generalSize.y };
			if (lol.intersects(collidePoints[4]) ||lol.intersects(collidePoints[5]))
			{ 
				collided = true; 
			}
		}
		//Left
			if ((*map)[eTileX - 1][eTileY].getType() == Tile::Solid)
		{
			sf::IntRect lol = { int(e->getPosition().x - generalSize.x) ,int(e->getPosition().y),generalSize.x,generalSize.y };
			if (lol.intersects(collidePoints[0]) || lol.intersects(collidePoints[1]))
				collided = true; 
		}
		//Up
			if ((*map)[eTileX][eTileY - 1].getType() == Tile::Solid)
		{
			sf::IntRect lol = { int(e->getPosition().x) , int(e->getPosition().y) - generalSize.y,generalSize.x,generalSize.y };
			if (lol.intersects(collidePoints[2]) || lol.intersects(collidePoints[3]))
				collided = true;
		}
		//Down
			if ((*map)[eTileX][eTileY + 1].getType() == Tile::Solid)
		{
			sf::IntRect lol = {int(e->getPosition().x),int(e->getPosition().y) + generalSize.y ,generalSize.x,generalSize.y};
			if (lol.intersects(collidePoints[6]) || lol.intersects(collidePoints[7])) 
				collided = true;
		}
	}
		
	std::vector<bool> colVec;
	colVec.push_back(collided);
	OurLua::setBooleans(l, colVec);

	return 1;
}
