#pragma once
#include "Tile.hpp"
#include <vector>
#include "..\Camera\Camera.hpp"

class Grid : public sf::Drawable
{
private:
	sf::Texture* m_spriteSheet;
	sf::Sprite m_displaySprite;
	std::string m_spritesheetPath;

	std::vector<std::vector<Tile>> m_tiles;	
	std::vector<Tile*> m_renderableTiles;

	bool m_cullTiles;

public:
	Grid(int width = 32, int height = 32, float sizeOfTile = 32.0f, int type = 0);
	Grid(const Grid& other);
	virtual ~Grid();
	
	void setTypeOfTile(int x, int y, int type);
	void setColorOfTile(int x, int y, int r, int g, int b);
	void setColorOfTile(int x, int y, const sf::Vector3i& color);
	void setTextureOfTile(int x, int y, const sf::IntRect& rect);

	void update(Camera* cam);

	int getWidth() const;
	int getHeight() const;
	sf::Vector2i getDimensions() const;
	const Tile& getTile(int x, int y);

	std::string toFile() const;

	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	Grid& operator=(const Grid& other);

	void LoadSpriteSheet(const std::string& path);

	// EDITOR {
		const sf::Sprite& getDisplaySprite() const;
		bool isSpritesheetLoaded() const;
		sf::Vector2u getSheetImageSize() const;
		void MarkMode();
		void NormalMode();
	// }
private:
	void _init(int width, int height, float sizeOfTile, int type);
	void _cleanup();
	void _copy(const Grid& other);

};