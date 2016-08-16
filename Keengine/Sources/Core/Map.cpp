#include "Map.hpp"

Map::Map()
{
}

LayerComponent* Map::addLayer()
{
	mLayers.push_back(LayerComponent());
	registerComponent(&mLayers.back());
	attachComponent(&mLayers.back());
	return &mLayers.back();
}

LayerComponent* Map::createLayer(Tileset* tileset, sf::Vector2i const& size, sf::Vector2i const& tileSize, std::string const& orientation, std::string const& staggerAxis, std::string const& staggerIndex, unsigned int hexSideLength)
{
	LayerComponent* layer = addLayer();
	if (layer != nullptr)
	{
		layer->create(tileset, size, tileSize, staggerAxis, staggerIndex, orientation, hexSideLength);
	}
	return layer;
}

std::size_t Map::getLayerCount()
{
	return mLayers.size();
}

LayerComponent* Map::getLayer(std::size_t index)
{
	if (0 <= index && index < mLayers.size())
	{
		return &mLayers[index];
	}
	return nullptr;
}

LayerComponent* Map::getLayer(std::string const& name)
{
	std::size_t size = mLayers.size();
	for (std::size_t i = 0; i < size; i++)
	{
		if (mLayers[i].getName() == name)
		{
			return &mLayers[i];
		}
	}
	return nullptr;
}

bool Map::hasLayer(std::string const& name)
{
	std::size_t size = mLayers.size();
	for (std::size_t i = 0; i < size; i++)
	{
		if (mLayers[i].getName() == name)
		{
			return true;
		}
	}
	return false;
}

void Map::removeLayer(std::size_t index)
{
	if (0 <= index && index < mLayers.size())
	{
		unregisterComponent(&mLayers[index]);
		detachComponent(&mLayers[index]);
		mLayers.erase(mLayers.begin() + index);
	}
}

void Map::removeLayer(std::string const & name)
{
	std::size_t size = mLayers.size();
	for (std::size_t i = 0; i < size; i++)
	{
		if (mLayers[i].getName() == name)
		{
			unregisterComponent(&mLayers[i]);
			detachComponent(&mLayers[i]);
			mLayers.erase(mLayers.begin() + i);
			size--;
		}
	}
}

const sf::Vector2i& Map::getSize() const
{
	return mSize;
}

void Map::setSize(sf::Vector2i const& size)
{
	mSize = size;
	for (std::size_t i = 0; i < mLayers.size(); i++)
	{
		mLayers[i].setSize(size);
	}
}

const sf::Vector2i& Map::getTileSize() const
{
	return mTileSize;
}

void Map::setTileSize(sf::Vector2i const& tileSize)
{
	mTileSize = tileSize;
	for (std::size_t i = 0; i < mLayers.size(); i++)
	{
		mLayers[i].setTileSize(tileSize);
	}
}

const std::string& Map::getOrientation() const
{
	return mOrientation;
}

void Map::setOrientation(std::string const& orientation)
{
	mOrientation = orientation;
	for (std::size_t i = 0; i < mLayers.size(); i++)
	{
		mLayers[i].setOrientation(orientation);
	}
}

const std::string& Map::getStaggerAxis() const
{
	return mStaggerAxis;
}

void Map::setStaggerAxis(std::string const& axis)
{
	mStaggerAxis = axis;
	for (std::size_t i = 0; i < mLayers.size(); i++)
	{
		mLayers[i].setStaggerAxis(axis);
	}
}

const std::string& Map::getStaggerIndex() const
{
	return mStaggerIndex;
}

void Map::setStaggerIndex(std::string const& index)
{
	mStaggerIndex = index;
	for (std::size_t i = 0; i < mLayers.size(); i++)
	{
		mLayers[i].setStaggerIndex(index);
	}
}

unsigned int Map::getHexSizeLength() const
{
	return mHexSideLength;
}

void Map::setHexSideLength(unsigned int hexSideLength)
{
	mHexSideLength = hexSideLength;
	for (std::size_t i = 0; i < mLayers.size(); i++)
	{
		mLayers[i].setHexSideLength(hexSideLength);
	}
}