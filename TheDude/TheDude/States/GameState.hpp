#pragma once
#include "State.hpp"
#include "..\Level\Level.hpp"

class GameState : public State
{
private:
	Level * m_currentLevel;


public:
	GameState(const std::string &levelPath);
	~GameState();

	void Update() override;
	void Draw() override;
private:
	void _init(const std::string &levelPath);
	void _cleanup();
protected:
	void Pop() override;
};