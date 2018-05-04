#pragma once
#pragma once 
#include "Grid.hpp" 
#include <string> 

class Level : public sf::Drawable
{
private:
	Grid * m_grid;
	std::string m_levelName;
	Camera* m_camera;
	sf::RenderWindow* m_pWindow;
	sf::Texture m_spriteSheet;
	std::vector<sf::Sprite> m_sprites;
	std::string m_spritesheetPath;
	bool typing;
public:
	Level(sf::RenderWindow* renderWindow);
	Level(const Level& other);
	~Level();
	void LoadLevel(const std::string& target);
	bool SaveLevel(const std::string& target);
	void Update();
	Level& operator=(const Level& other);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void _handleInput();
private:
	void _cleanup();
	void _copy(const Level& other);
};