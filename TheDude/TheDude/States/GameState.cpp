#include "GameState.hpp"

GameState::GameState(const std::string &levelPath)
{
	m_currentLevel = nullptr;
	_init(levelPath);
}

GameState::~GameState()
{
	delete m_currentLevel;
}

void GameState::Update()
{
	m_currentLevel->Update();
}

void GameState::Draw()
{
	s_window->draw(*m_currentLevel);
}

void GameState::_init(const std::string &levelPath)
{
	m_currentLevel = new Level(s_window);
	m_currentLevel->LoadLevel(levelPath);
}
