#include "Map.hpp"
#include "World.hpp"

Map::Map()
	: mLayers()
	, mTileset(nullptr)
	, mSize()
	, mTileSize()
	, mOrientation("orthogonal")
	, mStaggerAxis("y")
	, mStaggerIndex("odd")
	, mHexSideLength(0)
{
}

bool Map::loadTmxFile(std::string const& filename)
{
	clearLayers();
	if (filename == "")
	{
		return false;
	}
	pugi::xml_document doc;
	if (!doc.load_file(filename.c_str()))
	{
		return false;
	}
	std::string path;
	std::size_t found = filename.find_last_of("/");
	if (found != std::string::npos)
	{
		path = filename.substr(0, found + 1);
	}
	else
	{
		found = filename.find_last_of("\\");
		if (found != std::string::npos)
		{
			path = filename.substr(0, found + 1);
		}
		else
		{
			path = "";
		}
	}
	pugi::xml_node map = doc.child("map");
	if (!map)
	{
		return false;
	}
	for (pugi::xml_attribute attr = map.first_attribute(); attr; attr = attr.next_attribute())
	{
		if (attr.name() == std::string("orientation")) mOrientation = attr.as_string();
		if (attr.name() == std::string("width")) mSize.x = attr.as_int();
		if (attr.name() == std::string("height")) mSize.y = attr.as_int();
		if (attr.name() == std::string("tilewidth")) mTileSize.x = attr.as_int();
		if (attr.name() == std::string("tileheight")) mTileSize.y = attr.as_int();
		if (attr.name() == std::string("hexsidelength")) mHexSideLength = attr.as_uint();
		if (attr.name() == std::string("staggeraxis")) mStaggerAxis = attr.as_string();
		if (attr.name() == std::string("staggerindex")) mStaggerIndex = attr.as_string();
	}
	pugi::xml_node properties = map.child("properties");
	if (properties)
	{
		for (const pugi::xml_node& property : properties.children("property"))
		{
			std::string name = property.attribute("name").as_string();
			std::string value = property.attribute("value").as_string();
			setProperty(name, value);
		}
	}

	for (pugi::xml_node tileset = map.child("tileset"); tileset; tileset = tileset.next_sibling("tileset"))
	{
		mTileset = &getWorld().createResource<Tileset>(tileset.attribute("name").as_string(), tileset, path);
	}

	for (pugi::xml_node layer = map.child("layer"); layer; layer = layer.next_sibling("layer"))
	{
		addLayer()->loadFromNode(layer, mTileset, mSize, mTileSize, mOrientation, mStaggerAxis, mStaggerIndex, mHexSideLength);
	}
	return true;
}

bool Map::saveTmxFile(std::string const & filename)
{
	if (filename == "")
	{
		return false;
	}
	pugi::xml_document doc;
	pugi::xml_node map = doc.append_child("map");
	map.append_attribute("orientation") = mOrientation.c_str();
	map.append_attribute("width") = mSize.x;
	map.append_attribute("height") = mSize.y;
	map.append_attribute("tilewidth") = mTileSize.x;
	map.append_attribute("tileheight") = mTileSize.y;
	if (mHexSideLength != 0)
		map.append_attribute("hexsidelength") = mHexSideLength;
	if (mOrientation == "staggered" || mOrientation == "hexagonal")
	{
		map.append_attribute("staggeraxis") = mStaggerAxis.c_str();
		map.append_attribute("staggerindex") = mStaggerIndex.c_str();
	}

	if (mProperties.size() > 0)
	{
		pugi::xml_node properties = map.append_child("properties");
		for (auto itr = mProperties.begin(); itr != mProperties.end(); itr++)
		{
			pugi::xml_node property = properties.append_child("property");
			property.append_attribute("name") = itr->first.c_str();
			property.append_attribute("value") = itr->second.c_str();
		}
	}

	if (mTileset != nullptr)
	{
		pugi::xml_node tileset = map.append_child("tileset");
		mTileset->saveToNode(tileset);
	}

	for (std::size_t i = 0; i < mLayers.size(); i++)
	{
		pugi::xml_node layer = map.append_child("layer");
		mLayers[i].saveToNode(layer);
	}

	doc.save_file(filename.c_str(), " ");
	return true;
}

Tileset* Map::getTileset()
{
	return mTileset;
}

void Map::setTileset(Tileset * tileset)
{
	mTileset = tileset;
}

LayerComponent* Map::addLayer()
{
	mLayers.emplace_back();
	registerComponent(&mLayers.back());
	attachComponent(&mLayers.back());
	return &mLayers.back();
}

LayerComponent* Map::createLayer(std::string const& tilesetName, sf::Vector2i const& size, sf::Vector2i const& tileSize, std::string const& orientation, std::string const& staggerAxis, std::string const& staggerIndex, unsigned int hexSideLength)
{
	LayerComponent* layer = addLayer();
	if (layer != nullptr)
	{
		layer->create(&getWorld().getResource<Tileset>(tilesetName), size, tileSize, staggerAxis, staggerIndex, orientation, hexSideLength);
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

void Map::clearLayers()
{
	std::size_t size = mLayers.size();
	for (std::size_t i = 0; i < size; i++)
	{
		removeLayer(i);
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