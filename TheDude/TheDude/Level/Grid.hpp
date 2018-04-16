#pragma once
#include "Tile.hpp"
#include <vector>
#include <deque>
#include "..\Camera\Camera.hpp"

class Grid : public sf::Drawable
{
private:
	std::vector<std::vector<Tile>> m_tiles;
	std::deque<Tile> m_renderTiles;

public:
	Grid(int width = 32, int height = 32, float sizeOfTile = 32.0f, int type = 0);
	Grid(const Grid& other);
	virtual ~Grid() {};
	
	void setTypeOfTile(int x, int y, int type);
	void setColorOfTile(int x, int y, int r, int g, int b);
	void setColorOfTile(int x, int y, const sf::Vector3i& color);

	void update(Camera* cam);

	int getWidth() const;
	int getHeight() const;
	sf::Vector2i getDimensions() const;
	const Tile& getTile(int x, int y);

	void draw(sf::RenderTarget & target, sf::RenderStates states) const;

	Grid& operator=(const Grid& other);
private:
	void _init(int width, int height, float sizeOfTile, int type);
	void _cleanup();
	void _copy(const Grid& other);

};