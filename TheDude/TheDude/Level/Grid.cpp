#include "Grid.hpp"
#include <iostream>

Grid::Grid(int width, int height, float sizeOfTile, Tile::Type type)
{
	_init(width, height, sizeOfTile, type);
}

Grid::Grid(const Grid & other)
{
	_cleanup();
	_copy(other);
}

void Grid::setTypeOfTile(int x, int y, const Tile::Type & type)
{
	m_tiles[x][y].setType(type);
}

void Grid::setColorOfTile(int x, int y, float r, float g, float b)
{
	m_tiles[x][y].setColor(r, g, b);
}

int Grid::getWidth() const
{
	return m_tiles[0].size();
}

int Grid::getHeight() const
{
	return m_tiles.size();
}

sf::Vector2i Grid::getDimensions() const
{
	return sf::Vector2i(this->getHeight(), this->getWidth());
}

const Tile & Grid::getTile(int x, int y)
{
	return m_tiles[y][x];
}

void Grid::update(Camera* cam)
{
	for (auto& v : m_tiles)
	{
		for (auto& v2 : v)
		{
			v2.setShapePosition(sf::Vector2f(v2.getPosition()) + cam->getPosition());
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

Grid & Grid::operator=(const Grid & other)
{
	if (this != &other)
	{
		_cleanup();
		_copy(other);
	}

	return *this;
}

void Grid::_init(int width, int height, float sizeOfTile, Tile::Type type)
{
	for (int i = 0; i < height; i++)
	{
		m_tiles.push_back(std::vector<Tile>());
		for (int k = 0; k < width; k++)
		{
			Tile t(sizeOfTile, sizeOfTile, type);
			t.setPosition(static_cast<float>(i) * sizeOfTile , static_cast<float>(k) * sizeOfTile);
			m_tiles[i].push_back(t);
		}
	}
}

void Grid::_copy(const Grid & other)
{
	for (size_t i = 0; i < other.m_tiles.size(); i++)
	{
		m_tiles.push_back(std::vector<Tile>());
		for (size_t k = 0; other.m_tiles[i].size(); k++)
		{
			Tile t(other.m_tiles[i][k]);
			m_tiles[i].push_back(t);
		}
	}
}

void Grid::_cleanup()
{
	for (auto v : m_tiles)
	{
		v.clear();
	}
	m_tiles.clear();
}
