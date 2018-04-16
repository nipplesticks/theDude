#pragma once
#include "Grid.hpp"
#include <string>

class Level : public sf::Drawable
{
private:
	Grid * m_grid;
	std::string m_levelName;
	/*
		Player ctrl
		Enemy ctrl
		Item ctrl
		Projectile ctrl	
		Camera ctrl
	*/

public:
	Level();
	Level(const Level& other);
	~Level();
	void LoadLevel(const std::string & target);
	void Update();
	Level& operator=(const Level& other);
private:
	void _cleanup();
	void _copy(const Level& other);
};