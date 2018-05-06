#pragma once
#pragma once 
#include "Grid.hpp" 
#include <string> 

class Level : public sf::Drawable
{
private:
	Grid * m_grid;
	Camera* m_camera;
	sf::RenderWindow* m_pWindow;

	// EDITOR {
		bool m_closeFlag;
	// }

public:
	Level(sf::RenderWindow* renderWindow);
	Level(const Level& other);
	~Level();

	void LoadLevel(const std::string& target);
	bool SaveLevel(const std::string& target);

	void Update();
	// EDITOR {
		void EditorRender();
		bool isClose();
	// }
	Level& operator=(const Level& other);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:

	// EDITOR METHODS {
		void _toolbarRender();
		void _spritePaletteRender();
		void _entityPaletteRender();
	// }
	void _handleInput();
	void _cleanup();
	void _copy(const Level& other);
};