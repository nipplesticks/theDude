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
	
	void setTextureOfAllTiles(const sf::IntRect& rect);
	void setColorOfAllTiles(const sf::Color color, bool force = false);

	void MarkTiles(bool on);
	void setTypeOfTile(int x, int y, int type);

	void setColorOfTile(int x, int y, int r, int g, int b, bool perm = false);
	void setColorOfTile(int x, int y, const sf::Vector3i& color, bool perm = false);

	void setTextureOfTile(int x, int y, const sf::IntRect& rect);
	void removeTextureOfTile(int x, int y);

	const std::vector<std::vector<Tile>>* getTiles() const;

	void update(Camera* cam);

	std::vector<sf::Vector2i> getGoalTilesPositions() const;

	int getWidth() const;
	int getHeight() const;
	sf::Vector2i getDimensions() const;
	const Tile& getTile(int x, int y);

	std::string toFile() const;

	void draw(sf::RenderTarget & target, sf::RenderStates states) const;

	
	sf::Vector2f getTileDim() const;

	void UnloadSpriteSheet();
	void LoadSpriteSheet(const std::string& path);

	Grid& operator=(const Grid& other);
	// EDITOR {
		const sf::Sprite& getDisplaySprite() const;
		bool isSpritesheetLoaded() const;
		sf::Vector2u getSheetImageSize() const;
	// }
private:
	void _init(int width, int height, float sizeOfTile, int type);
	void _cleanup();
	void _copy(const Grid& other);

};