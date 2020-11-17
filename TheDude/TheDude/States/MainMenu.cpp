#include "MainMenu.hpp"
#include "Game.hpp"
#include "Editor.hpp"
#include <filesystem>
#include <sstream>


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
	delete m_returnToMM;
	for (auto& bt : m_levelButton)
	{
		delete bt;
	}
}

void MainMenu::Update()
{
	sf::Vector2i mp = sf::Mouse::getPosition(*s_window);
	if (m_showLevels)
	{
		_displayLevels();
	}
	else
	{
		m_Game->Update(mp);
		m_Editor->Update(mp);
		m_Exit->Update(mp);

	}
}

void MainMenu::Draw()
{
	s_window->draw(m_bck);
	_moveBackground();
	if (m_showLevels)
	{
		for (auto& bt : m_levelButton)
			bt->draw(*s_window, sf::RenderStates::Default);

		m_returnToMM->draw(*s_window, sf::RenderStates::Default);
	}
	else
	{
		m_Game->draw(*s_window, sf::RenderStates::Default);
		m_Editor->draw(*s_window, sf::RenderStates::Default);
		m_Exit->draw(*s_window, sf::RenderStates::Default);

	}

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

	pxSizeX = s_window->getSize().x *0.05f;
	pxSizeY = s_window->getSize().y *0.05f;

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

	m_Game->setFunctionPointer(std::bind(&MainMenu::_displayLevels, this));
	m_Editor->setFunctionPointer(std::bind(&MainMenu::_pushEditor, this));
	m_Exit->setFunctionPointer(std::bind(&MainMenu::Pop, this));
}
void MainMenu::_displayLevels()
{
	auto levels = getfilesInDir();
	if (!m_showLevels)
	{
		float winX = s_window->getSize().x;
		float winY = s_window->getSize().y;
		delete m_returnToMM;
		for (auto& bt : m_levelButton)
		{
			delete bt;
		}
		m_levelButton.clear();
		int counterX = 1;
		int counterY = 0;
		for (int i = 0; i < levels.size(); i++)
		{
			std::string l = levels[i];
			l.erase(l.begin() + l.find_last_of('.'), l.end());
			int buttonSize = 200;
			int padding = 10;

			int xPos = counterX++ * (winX / (levels.size() + 1));
			int yPos = counterY * buttonSize;
			Button* bt = new Button(xPos - (buttonSize/2) , yPos + padding , buttonSize, buttonSize);
		/*	if (counterX == 5)
			{
				counterX = 1;
				counterY++;
			}*/
			bt->setButtonText(l);
			m_levelButton.push_back(bt);
		
		}
		
		m_showLevels = true;
		m_returnToMM = new Button(winX - 350, winY - 120, 300, 100);
		m_returnToMM->setButtonText("Return to main menu");
		m_returnToMM->setFunctionPointer(std::bind(&MainMenu::_disableShowLevels, this));
	}

	sf::Vector2i mp = sf::Mouse::getPosition(*s_window);
	for (auto& bt : m_levelButton)
	{
		if (bt->Update(mp))
		{
			_pushGame(bt->getTextString());
		}
	}

	m_returnToMM->Update(mp);


}
void MainMenu::_disableShowLevels()
{
	m_showLevels = false;
}
#include "../Hack.hpp"
void MainMenu::_pushGame(std::string level)
{
	
	Hack::g = new Game(level);
	State::Push(Hack::g);
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
	static sf::Vector2f m(pxSizeX *0.5f, pxSizeY *0.5f);

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
		if (abs(counter) >= 356)
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

std::vector<std::string> MainMenu::getfilesInDir()
{
	std::vector<std::string> files;

	// Stupid but works
	std::string folderPath = __FILE__;
	folderPath += "/../../";
	folderPath += "Resourses/Levels";
	namespace fs = std::filesystem;
	for (const std::filesystem::directory_entry p : fs::directory_iterator(folderPath))
	{
		std::stringstream s;
		const std::filesystem::path pp = p.path();
		s << pp << std::endl;
		std::string lol(s.str());
		std::string relative;
		for (size_t i = lol.find_last_of('\\'); i < lol.size() - 1; i++)
			relative += lol[i];

		files.push_back(relative);

	}

	return files;
}
