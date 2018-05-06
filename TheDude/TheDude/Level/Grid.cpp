#include "Grid.hpp"
#include <iostream>

Grid::Grid(int width, int height, float sizeOfTile, int type)
	: m_spriteSheet(nullptr)
{
	_init(width, height, sizeOfTile, type);
}

Grid::Grid(const Grid & other)
{
	_cleanup();
	_copy(other);
}

Grid::~Grid()
{
	delete m_spriteSheet;

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

void Grid::setTextureOfTile(int x, int y, const sf::IntRect& rect)
{
	if (nullptr == m_spriteSheet)
	{
		std::cout << __LINE__ << ": Spritesheet not loaded!";
		return;
	}
	
	m_tiles[x][y].setTexture(*m_spriteSheet, rect);
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
	int size = static_cast<int>(m_tiles[0][0].getSize().x + 0.5f);
	map += "grid " + std::to_string(m_tiles.size()) + " " + std::to_string(m_tiles[0].size()) + " " +
		std::to_string(size) + " " + std::to_string(0) + '\n';

	// grid sizeX sizeY tileSize 0 
	// sheet <PATH>
	map += "sheet" + m_spritesheetPath + "\n";

	for (size_t i = 0; i < m_tiles.size(); i++)
	{
		for (size_t k = 0; k < m_tiles[i].size(); k++)
		{
			map += "t " + std::to_string(i) + " " + std::to_string(k) + " " + 
				std::to_string(m_tiles[i][k].getType()) + " ";

			sf::Color c = m_tiles[i][k].getColor();
			map += std::to_string(c.r) + " " + std::to_string(c.g) + " " + std::to_string(c.b) + " ";
			sf::IntRect ir = m_tiles[i][k].getTextureRect();
			map += std::to_string(ir.left) + " " + std::to_string(ir.top) + "\n";
		}
	}

	return map;
}

void Grid::update(Camera* cam)
{
	m_renderableTiles.clear();
	m_renderableTiles.reserve(m_tiles.size()*m_tiles.size());
	int scale = static_cast<int>(m_tiles[0][0].getSize().x);
	int startX = static_cast<int>(-cam->getPosition().x / scale);
	int startY = static_cast<int>(-cam->getPosition().y / scale);
	int endX = startX + ( (cam->getWindowWidth()) / scale);
	int endY = startY + ( (cam->getWindowHeight()) / scale);
//	std::cout << startX << "," << endX << std::endl;
	//std::cout << startY << "," << endY << std::endl;
	
	for (int i = startX; i < endX; i++)
	{
		if (i < 0 || i >= m_tiles.size()) continue;

		for (int j = startY; j < endY; j++)
		{
			if (j < 0 || j >= m_tiles[i].size()) continue;
			
			m_renderableTiles.push_back(&m_tiles[i][j]);
			m_tiles[i][j].setShapePosition(sf::Vector2f(m_tiles[i][j].getPosition()) + cam->getPosition());

		}
	}
}

void Grid::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	//std::cout << m_renderableTiles.size() << std::endl;
	for (auto& tiles : m_renderableTiles)
		target.draw(*tiles, states);
	
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

void Grid::LoadSpriteSheet(const std::string & path)
{
	m_spritesheetPath = path;
	if (!m_spriteSheet)
	{
		m_spriteSheet = new sf::Texture();
	}
	m_spriteSheet->loadFromFile(m_spritesheetPath);
	m_displaySprite.setTexture(*m_spriteSheet);

}

const sf::Sprite & Grid::getDisplaySprite() const
{
	return m_displaySprite;
}

bool Grid::isSpritesheetLoaded() const
{
	return m_spriteSheet != nullptr;
}

sf::Vector2u Grid::getSheetImageSize() const
{
	return m_spriteSheet->getSize();
}

void Grid::_init(int width, int height, float sizeOfTile, int type)
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
	delete m_spriteSheet;
}
