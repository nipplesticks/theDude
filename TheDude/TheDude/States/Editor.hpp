#pragma once
#include "State.hpp"
#include "../Level/Level.hpp"

class Editor : public State
{
private:
	Level level;
public:
	Editor();
	~Editor();

	void Update() override;
	void Draw() override;

};