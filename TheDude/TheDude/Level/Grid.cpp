#include "Grid.hpp"
#include <iostream>

Grid::Grid(int width, int height, float sizeOfTile, Tile::Type type)
{
	_init(width, height, sizeOfTile, type);
}

void Grid::setTypeOfTile(int x, int y, const Tile::Type & type)
{
	m_tiles[x][y].setType(type);
}

void Grid::setColorOfTile(int x, int y, float r, float g, float b)
{
	m_tiles[x][y].setColor(r, g, b);
}

void Grid::update()
{
	for (size_t i = 0; i < m_tiles.size(); i++)
	{
		for (size_t j = 0; j < m_tiles[i].size(); j++)
		{

			m_tiles[i][j].setPosition(m_tiles[i][j].getPosition() + cam.getDeltaPosition());
		}
	}
}

void Grid::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	
	for (size_t i = 0; i < m_tiles.size(); i++)
	{
		for (size_t k = 0; k < m_tiles[i].size(); k++)
		{
			m_tiles[i][k].draw(target, states);
		}
	}
}

void Grid::_init(int width, int height, float sizeOfTile, Tile::Type type)
{
	for (int i = 0; i < width; i++)
	{
		m_tiles.push_back(std::vector<Tile>());
		for (int k = 0; k < height; k++)
		{
			Tile t(sizeOfTile, sizeOfTile, type);
			t.setPosition(static_cast<float>(i) * sizeOfTile , static_cast<float>(k) * sizeOfTile);
			m_tiles[i].push_back(t);
		}
	}
}
