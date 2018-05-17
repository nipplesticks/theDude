#include "MainMenu.hpp"
#include "Game.hpp"
#include "Editor.hpp"

MainMenu::MainMenu()
{
	_init();
}

MainMenu::~MainMenu()
{
	delete m_Game;
	delete m_Exit;
	delete m_Editor;
	delete px;
}

void MainMenu::Update()
{
	sf::Vector2i mp = sf::Mouse::getPosition(*s_window);

	m_Game->Update(mp);
	m_Editor->Update(mp);
	m_Exit->Update(mp);
}

void MainMenu::Draw()
{
	s_window->draw(m_bck);
	_moveBackground();

	m_Game->draw(*s_window, sf::RenderStates::Default);
	m_Editor->draw(*s_window, sf::RenderStates::Default);
	m_Exit->draw(*s_window, sf::RenderStates::Default);

}

void MainMenu::_init()
{
	int width = 300;
	int height = 100;
	int distX = 0;
	int distY = 10;
	int startX = s_window->getSize().x / 2 - width / 2;
	int startY = s_window->getSize().y / 2 - (height + distY) * 1.5;

	m_bck.setPosition(0, 0);
	m_bck.setSize(sf::Vector2f(s_window->getSize().x, s_window->getSize().y));

	pxSizeX = s_window->getSize().x * 0.20f;
	pxSizeY = s_window->getSize().y * 0.20f;

	m_t.create(pxSizeX, pxSizeY);
	m_bck.setTexture(&m_t);

	px_size = pxSizeX * pxSizeY * 4;
	px = new sf::Uint8[px_size];

	for (int i = 0; i < px_size; i += 4)
	{
		px[i + 3] = 255;
	}
	_moveBackground();


	m_Game = new Button(startX, startY, width, height);
	m_Game->setButtonText("Play_Game");
	m_Editor = new Button(startX, startY + height + distY, width, height);
	m_Editor->setButtonText("Create_Map");
	m_Exit = new Button(startX, startY + (height + distY) * 2, width, height);
	m_Exit->setButtonText("Exit_Game");
	m_Game->setFunctionPointer(std::bind(&MainMenu::_pushGame, this));
	m_Editor->setFunctionPointer(std::bind(&MainMenu::_pushEditor, this));
	m_Exit->setFunctionPointer(std::bind(&MainMenu::Pop, this));
}

void MainMenu::_pushGame()
{
	State::Push(new Game);
}

void MainMenu::_pushEditor()
{
	State::Push(new Editor);
}

void MainMenu::_moveBackground()
{
	sf::Vector2i mp = sf::Mouse::getPosition(*s_window);
	static int counter = 0;
	static bool add = true;
	static int canUpdate = 0;
	sf::Vector2f m(pxSizeX *0.5f, pxSizeY *0.5f);

	for (int x = 0; x < (int)pxSizeX; x++)
	{
		for (int y = 0; y < (int)pxSizeY; y++)
		{
			int index = (x + y * pxSizeX) * 4;

			sf::Vector2f p(x, y);
			
			sf::Vector2f l = p - m;
			float length = l.x * l.x + l.y * l.y;

			float noice = length - abs(counter);

			px[index + 0] = (x + (int)(noice * 0.5)) % 256;
			px[index + 1] = (y + (int)(noice * 0.5)) % 256;
			px[index + 2] = abs(counter + (int)(noice * 0.5)) % 256;
		}
	}
	if (canUpdate > 2)
		canUpdate = 0;

	if (canUpdate == 0)
	{
		if (abs(counter) >= 255)
			add = !add;
		if (add)
			counter++;
		else
			counter--;

		canUpdate++;
	}
	else
		canUpdate++;


	m_t.update(px);
}
