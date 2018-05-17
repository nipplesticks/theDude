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
		bool m_spritePaletteOpen;
		bool m_entityPaletteOpen;
		bool m_tileTypePaletteOpen;
		bool m_tileColorPaletteOpen;

		std::string m_currentTool;
		bool		m_activeTool[4];

#define TOOL_SPRITE 0
#define TOOL_ENTITY 1
#define TOOL_TYPE 2
#define TOOL_COLOR 3

		struct EntityTexGroup
		{
			std::string texturePath;
			std::vector<sf::Vector2f> m_entityPositions;
		};
		std::vector<EntityTexGroup> m_entityTexGroups;

		struct TextureWPath
		{
			sf::Texture texture;
			std::string path;
		};
		std::vector<TextureWPath> m_entityInstanceTextures;

		// Only for displaying entities in the editor not during runtime
		std::vector<sf::Vector2f> m_entityInstancePositions;
		std::vector<sf::RectangleShape> m_entityInstanceShapes;
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
		void _tileTypePaletteRender();
		void _tileColorPaletteRender();
		bool _IsClickInside() const;
		bool _IsMouseInside() const;
		std::vector<std::string> filesInDir(std::string path);
		void _changeCurrentTool(int index, std::string tool, bool NormalMode);
		
		template<std::size_t N1>
		void _resetArray(std::array<bool, N1> & a, int index)
		{
			memset(&a, 0, N1);
			a[index] = true;
		}
		std::string getTexturePath(std::string luafile) const;
	// }
	void _cleanup();
	void _copy(const Level& other);
};