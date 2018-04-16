#include "Grid.hpp"

Grid::Grid(int width, int height, float sizeOfTile, int type)
{
	_init(width, height, sizeOfTile, type);
}

Grid::Grid(const Grid & other)
{
	_cleanup();
	_copy(other);
}

void Grid::setTypeOfTile(int x, int y, int type)
{
	m_tiles[x][y].setType(type);
}

void Grid::setColorOfTile(int x, int y, int r, int g, int b)
{
	m_tiles[x][y].setColor(r, g, b);
}

void Grid::setColorOfTile(int x, int y, const sf::Vector3i& color)
{
	this->setColorOfTile(x, y, color.x, color.y, color.z);
}

int Grid::getWidth() const
{
	return static_cast<int>(m_tiles[0].size());
}

int Grid::getHeight() const
{
	return static_cast<int>(m_tiles.size());
}

sf::Vector2i Grid::getDimensions() const
{
	return sf::Vector2i(this->getHeight(), this->getWidth());
}

const Tile & Grid::getTile(int x, int y)
{
	return m_tiles[x][y];
}

std::string Grid::toFile() const
{
	std::string map = "";
	map += "grid " + std::to_string(m_tiles.size()) + " " + std::to_string(m_tiles[0].size()) + " " +
		std::to_string(m_tiles[0][0].getSize().x) + " " + std::to_string(0) + '\n';

	for (size_t i = 0; i < m_tiles.size(); i++)
	{
		for (size_t k = 0; k < m_tiles[i].size(); k++)
		{
			map += "t " + std::to_string(m_tiles[i][k].getPosition().x) + " " + std::to_string(m_tiles[i][k].getPosition().y) + " " + 
				std::to_string(m_tiles[i][k].getType()) + " ";

			sf::Color c = m_tiles[i][k].getColor();
			map += std::to_string(c.r) + " " + std::to_string(c.g) + " " + std::to_string(c.b) + '\n';
		}
	}

	return map;
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

void Grid::_init(int width, int height, float sizeOfTile, int type)
{
	for (int i = 0; i < height; i++)
	{
		m_tiles.push_back(std::vector<Tile>());
		for (int k = 0; k < width; k++)
		{
			Tile t(sizeOfTile, sizeOfTile, type);
			t.setPosition(static_cast<float>(i) * sizeOfTile, static_cast<float>(k) * sizeOfTile);
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
