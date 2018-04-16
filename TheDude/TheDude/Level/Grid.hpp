#pragma once
#include "Tile.hpp"
#include <vector>
#include "..\Camera\Camera.hpp"

class Grid : public sf::Drawable
{
private:
	std::vector<std::vector<Tile>> m_tiles;

public:
	Grid(int width = 32, int height = 32, float sizeOfTile = 16.0f, Tile::Type type = Tile::Type::Water);
	
	virtual ~Grid() {};
	
	void setTypeOfTile(int x, int y, const Tile::Type &type);
	void setColorOfTile(int x, int y, float r, float g, float b);

	void update();

	int getWidth() const;
	int getheight() const;
	const sf::Vector2i& getDimensions() const;
	const Tile& getTile(int x, int y);

	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
private:
	void _init(int width, int height, float sizeOfTile, Tile::Type type);

};