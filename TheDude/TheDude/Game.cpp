#include "Game.hpp"

std::vector<sf::Shape*> Render::renderQueue;
bool Game::s_isGameRunning = true;

Game::Game()
{
	m_entityHandler = nullptr;
	p_wnd = nullptr;
}

Game::~Game()
{
	delete m_entityHandler;
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


	for (auto & thing : Render::renderQueue)
		p_wnd->draw(*thing);
	p_wnd->display();
}

void Game::_init()
{
	_initEntityHandler();
}

void Game::_initEntityHandler()
{
	m_entityHandler = new OurLua("Scripts/EntityHandler.Lua");
	_pushFunctions();
	m_entityHandler->InitLua();
}

void Game::_pushFunctions()
{
	m_entityHandler->PushFunction(CheckCollision, "CheckCollision");
	m_entityHandler->PushFunction(isKeyPressed, "isKeyPressed");
	m_entityHandler->PushFunction(ExitGame, "ExitGame");

	luaL_Reg enemyFunctions[]
	{
		{ "Create", Enemy::s_CreateEnemy },
		{ "setPosition", Enemy::s_setPosition },
		{ "getPosition", Enemy::s_getPosition },
		{ "setColor", Enemy::s_setColor },
		{ "move", Enemy::s_move },
		{ "draw", Enemy::s_draw },
		{ "__gc", Enemy::s_DestroyEnemy },
		{ NULL, NULL }
	};
	m_entityHandler->PushClassFunctions(Enemy::meta, enemyFunctions, "Enemy");

	luaL_Reg playerfunctions[]
	{
		{ "Create", TheDude::s_CreateTheDude },
		{ "setPosition", TheDude::s_setPosition },
		{ "setColor", TheDude::s_setColor },
		{ "move", TheDude::s_move },
		{ "draw", TheDude::s_draw },
		{ "__gc", TheDude::s_DestroyTheDude },
		{ NULL, NULL }
	};
	m_entityHandler->PushClassFunctions(TheDude::meta, playerfunctions, "Player");

}

int Game::isKeyPressed(lua_State * l)
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

int Game::CheckCollision(lua_State * l)
{
	std::vector<Entity**> e = OurLua::getInstancePointer<Entity>(l, 2);
	std::vector<bool> col;
	col.push_back(false);
	sf::Vector2f p0, p1, s0, s1;
	p0 = (*e[0])->getSelf().getPosition();
	p1 = (*e[1])->getSelf().getPosition();
	s0 = (*e[0])->getSelf().getSize();
	s1 = (*e[1])->getSelf().getSize();

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

int Game::ExitGame(lua_State * l)
{
	Game::s_isGameRunning = false;
	return 0;
}
