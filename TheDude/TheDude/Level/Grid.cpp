#include "Grid.hpp"
#include <iostream>

Grid::Grid(int width, int height, float sizeOfTile, int type)
	: m_spriteSheet(nullptr)
{
	_init(width, height, sizeOfTile, type);
	m_cullTiles = false;
}

Grid::Grid(const Grid & other)
{
	_cleanup();
	_copy(other);
}

Grid::~Grid()
{
	_cleanup();
}

void Grid::setTextureOfAllTiles(const sf::IntRect & rect)
{
	for (auto& row : m_tiles)
	{
		for (auto& col : row)
		{
			col.setTexture(*m_spriteSheet, rect);
		}
	}
}

void Grid::setColorOfAllTiles(const sf::Color color, bool force)
{
	for (auto& row : m_tiles)
	{
		for (auto& col : row)
		{
			col.setColor(color, force);
		}
	}
}

void Grid::setTypeOfTile(int x, int y, int type)
{
	m_tiles[x][y].setType(type);
}

void Grid::setColorOfTile(int x, int y, int r, int g, int b, bool perm)
{
	m_tiles[x][y].setColor(r, g, b, perm);
}

void Grid::setColorOfTile(int x, int y, const sf::Vector3i& color, bool perm)
{
	this->setColorOfTile(x, y, color.x, color.y, color.z, perm);
}

void Grid::setTextureOfTile(int x, int y, const sf::IntRect& rect)
{
	if (nullptr == m_spriteSheet)
	{
		std::cout << __LINE__ << ": Spritesheet not loaded!" << std::endl;
		return;
	}

	if (rect.left == -1)
	{
		m_tiles[x][y].RemoveTexture();
		
	}
	else
		m_tiles[x][y].setTexture(*m_spriteSheet, rect);
}

void Grid::removeTextureOfTile(int x, int y)
{
	m_tiles[x][y].RemoveTexture();
}

const std::vector<std::vector<Tile>>* Grid::getTiles() const
{
	return &m_tiles;
}

int Grid::getWidth() const
{
	return static_cast<int>(m_tiles.size());
}

int Grid::getHeight() const
{
	return static_cast<int>(m_tiles[0].size());
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

	map += "sheet " + m_spritesheetPath + "\n";

	for (size_t i = 0; i < m_tiles.size(); i++)
	{
		for (size_t k = 0; k < m_tiles[i].size(); k++)
		{
			map += "t " + std::to_string(i) + " " + std::to_string(k) + " " + 
				std::to_string(m_tiles[i][k].getType()) + " ";

			sf::Color c = m_tiles[i][k].getColor();
			map += std::to_string(c.r) + " " + std::to_string(c.g) + " " + std::to_string(c.b) + " ";
			if (m_tiles[i][k].hasTexture())
			{
				sf::IntRect ir = m_tiles[i][k].getTextureRect();
				map += std::to_string(ir.left) + " " + std::to_string(ir.top) + "\n";
			}
			else
				map += "-1 -1\n";
		}
	}

	return map;
}

void Grid::update(Camera* cam)
{
	// Culling
	static sf::Vector2f oldPos = cam->getPosition();
	sf::Vector2f currentCamPos = cam->getPosition();

	do
	{
		m_renderableTiles.clear();

		int scale = static_cast<int>(m_tiles[0][0].getSize().x);
		int startX = static_cast<int>(-cam->getPosition().x) >> 5;
		int startY = static_cast<int>(-cam->getPosition().y) >> 5;

		int endX = (startX + ((cam->getWindowWidth()) >> 5) + 1 );
		int endY = (startY + ((cam->getWindowHeight()) >> 5) + 2);

		for (int i = startX; i < endX; i++)
		{
			if (!(i < 0 || i >= m_tiles.size()))
			{
				for (int j = startY; j < endY; j++)
				{
					if (!(j < 0 || j >= m_tiles[i].size()))
					{
						m_tiles[i][j].setShapePosition(sf::Vector2f(m_tiles[i][j].getPosition()) + cam->getPosition());
						m_renderableTiles.push_back(&m_tiles[i][j]);
					}
				}
			}
		}
		oldPos = currentCamPos;
	} while (oldPos != currentCamPos);

	
}

void Grid::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	for (auto& t : m_renderableTiles)
		target.draw(*t);
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

sf::Vector2f Grid::getTileDim() const
{
	return m_tiles[0][0].getSize();
}

void Grid::UnloadSpriteSheet()
{
	delete m_spriteSheet;
	m_spriteSheet = nullptr;
	m_spritesheetPath = "";
	m_displaySprite = sf::Sprite();
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

void Grid::MarkMode()
{
	for (auto& t : m_tiles)
		for (auto &t2 : t)
			t2.ApplyTypeColor();
}

void Grid::NormalMode()
{
	for (auto& t : m_tiles)
		for (auto &t2 : t)
			t2.RemoveColors();
}


void Grid::_init(int width, int height, float sizeOfTile, int type)
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
