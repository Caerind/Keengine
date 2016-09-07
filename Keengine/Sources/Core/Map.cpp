#include "Map.hpp"
#include "Scene.hpp"

namespace ke
{

std::vector<sf::Vector2i> Map::getNeighboors(sf::Vector2i const & coords, std::string const & orientation, bool diag, std::string const& staggerIndex , std::string const& staggerAxis)
{
	if (orientation == "orthogonal")
	{
		std::vector<sf::Vector2i> n;
		n.push_back({ coords.x, coords.y - 1 });
		n.push_back({ coords.x, coords.y + 1 });
		n.push_back({ coords.x - 1, coords.y });
		n.push_back({ coords.x + 1, coords.y });
		if (diag)
		{
			n.push_back({ coords.x + 1, coords.y - 1 });
			n.push_back({ coords.x + 1, coords.y + 1 });
			n.push_back({ coords.x - 1, coords.y + 1 });
			n.push_back({ coords.x - 1, coords.y - 1 });
		}
		return n;
	}
	else if (orientation == "isometric")
	{
		// TODO : Conversion
		std::vector<sf::Vector2i> n;
		return n;
	}
	else if (orientation == "staggered")
	{
		// TODO : Use stagger
		std::vector<sf::Vector2i> n;
		if (coords.y % 2 == 0)
		{
			n.push_back({ coords.x - 1, coords.y - 1 });
			n.push_back({ coords.x, coords.y - 1 });
			n.push_back({ coords.x, coords.y + 1 });
			n.push_back({ coords.x - 1, coords.y + 1 });
		}
		else
		{
			n.push_back({ coords.x, coords.y - 1 });
			n.push_back({ coords.x + 1, coords.y - 1 });
			n.push_back({ coords.x + 1, coords.y + 1 });
			n.push_back({ coords.x, coords.y + 1 });
		}
		if (diag)
		{
			n.push_back({ coords.x, coords.y - 1 });
			n.push_back({ coords.x + 1, coords.y });
			n.push_back({ coords.x, coords.y + 1 });
			n.push_back({ coords.x - 1, coords.y });
		}
		return n;
	}
	else if (orientation == "hexagonal")
	{
		// TODO : Conversion
		std::vector<sf::Vector2i> n;
		return n;
	}
	else
	{
		// Unknown
		return std::vector<sf::Vector2i>();
	}
}

sf::Vector2i Map::worldToCoords(sf::Vector2f const & world, std::string const & orientation, sf::Vector2i const & tileSize, std::string const & staggerIndex, std::string const & staggerAxis, unsigned int hexSide)
{
	if (orientation == "orthogonal")
	{
		return sf::Vector2i((int)world.x / tileSize.x, (int)world.y / tileSize.y);
	}
	else if (orientation == "isometric")
	{
		// TODO : Conversion isometric
		return sf::Vector2i();
	}
	else if (orientation == "staggered")
	{
		sf::Vector2f s = sf::Vector2f(tileSize.x * 0.5f, tileSize.y * 0.5f);
		sf::Vector2f mc = sf::Vector2f(floor(world.x / s.x), floor(world.y / s.y));
		sf::Vector2f p = world - sf::Vector2f(mc.x * s.x, mc.y * s.y);
		const float rad = 0.523599f; // = 30 degrees
		int indexInt = (staggerIndex == "odd") ? 0 : 1;
		if (staggerAxis == "y")
		{
			if (((int)mc.x + (int)mc.y) % 2 == indexInt)
			{
				if (std::atan2(s.y - p.y, p.x) > rad)
				{
					mc.x--;
					mc.y--;
				}
			}
			else
			{
				(std::atan2(-p.y, p.x) > -rad) ? mc.y-- : mc.x--;
			}
			return sf::Vector2i((int)floor(mc.x * 0.5f), (int)mc.y);
		}
		else
		{
			if (((int)mc.x + (int)mc.y) % 2 == indexInt)
			{
				if (std::atan2(s.x - p.x, p.y) > rad)
				{
					mc.x--;
					mc.y--;
				}
			}
			else
			{
				(std::atan2(-p.x, p.y) > -rad) ? mc.x-- : mc.y--;
			}
			return sf::Vector2i((int)mc.x, (int)floor(mc.y * 0.5f));
		}
	}
	else if (orientation == "hexagonal")
	{
		// TODO : Conversion hexagonal
		return sf::Vector2i();
	}
	else
	{
		// Unknown
		return sf::Vector2i();
	}
}

sf::Vector2f Map::coordsToWorld(sf::Vector2i const & coords, std::string const & orientation, sf::Vector2i const & tileSize, std::string const & staggerIndex, std::string const & staggerAxis, unsigned int hexSide)
{
	if (orientation == "orthogonal")
	{
		return { coords.x * tileSize.x + 0.5f * tileSize.x, coords.y * tileSize.y + 0.5f * tileSize.y };
	}
	else if (orientation == "isometric")
	{
		// TODO : Conversion
		return sf::Vector2f();
	}
	else if (orientation == "staggered")
	{
		// TODO : Use stagger
		sf::Vector2f ret;
		ret.y = coords.y * tileSize.y * 0.5f + tileSize.y * 0.5f;
		if (coords.y % 2 == 0)
		{
			ret.x = coords.x * tileSize.x + tileSize.x * 0.5f;
		}
		else
		{
			ret.x = static_cast<float>(coords.x * tileSize.x + tileSize.x);
		}
		return ret;
	}
	else if (orientation == "hexagonal")
	{
		// TODO : Conversion
		return sf::Vector2f();
	}
	else
	{
		// Unknown
		return sf::Vector2f();
	}
}

Map::Map(Scene& scene)
	: Actor(scene)
	, mLayers()
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
	
	loadProperties(map);

	for (pugi::xml_node tileset = map.child("tileset"); tileset; tileset = tileset.next_sibling("tileset"))
	{
		mTileset = &getApplication().createResource<Tileset>(tileset.attribute("name").as_string(), tileset, path);
	}

	for (pugi::xml_node layer = map.child("layer"); layer; layer = layer.next_sibling("layer"))
	{
		LayerComponent::Ptr layerPtr = createComponent<LayerComponent>();
		attachComponent(layerPtr);
		layerPtr->loadFromNode(layer, mTileset, mSize, mTileSize, mOrientation, mStaggerAxis, mStaggerIndex, mHexSideLength);
	}

	for (pugi::xml_node imagelayer = map.child("imagelayer"); imagelayer; imagelayer = imagelayer.next_sibling("imagelayer"))
	{
		SpriteComponent::Ptr image = createComponent<SpriteComponent>();
		attachComponent(image);
		sf::Vector2f offset;
		for (const pugi::xml_attribute& attr : imagelayer.attributes())
		{
			if (attr.name() == std::string("offsetx"))
			{
				offset.x = attr.as_float();
			}
			if (attr.name() == std::string("offsety"))
			{
				offset.y = attr.as_float();
			}
			if (attr.name() == std::string("opacity"))
			{
				image->setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(255 * attr.as_float())));
			}
			if (attr.name() == std::string("visible"))
			{
				image->setVisible((attr.value() == "true"));
			}
		}
		image->setPosition(offset);
		pugi::xml_node img = imagelayer.child("image");
		if (img)
		{
			std::string source = img.attribute("source").as_string();
			if (source != "")
			{
				if (!getApplication().hasResource(source))
				{
					getApplication().createResource<Texture>(source, path + source);
				}
				image->setTexture(source);
			}
		}
		pugi::xml_node properties = imagelayer.child("properties");
		if (properties)
		{
			for (const pugi::xml_node& property : properties.children("property"))
			{
				if (property.attribute("name").as_string() == std::string("z"))
				{
					image->setZ(property.attribute("value").as_float());
				}
			}
		}
	}

	for (pugi::xml_node group = map.child("objectgroup"); group; group = group.next_sibling("objectgroup"))
	{
		for (pugi::xml_node object = group.child("object"); object; object = object.next_sibling("object"))
		{
			
		}
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

	saveProperties(map);

	if (mTileset != nullptr)
	{
		pugi::xml_node tileset = map.append_child("tileset");
		mTileset->saveToNode(tileset);
	}

	for (std::size_t i = 0; i < mLayers.size(); i++)
	{
		pugi::xml_node layer = map.append_child("layer");
		mLayers[i]->saveToNode(layer);
	}

	for (std::size_t i = 0; i < mImages.size(); i++)
	{
		std::shared_ptr<SpriteComponent> image = mImages[i];
		pugi::xml_node imagelayer = map.append_child("imagelayer");
		imagelayer.append_attribute("name") = std::string("ImageLayer" + std::to_string(i)).c_str();
		if (image->getPosition() != sf::Vector2f())
		{
			imagelayer.append_attribute("offsetx") = image->getPosition().x;
			imagelayer.append_attribute("offsety") = image->getPosition().y;
		}
		if (image->getColor() != sf::Color(255, 255, 255, 255))
		{
			imagelayer.append_attribute("opacity") = ((float)image->getColor().a) / 255.f;
		}
		if (!image->isVisible())
		{
			imagelayer.append_attribute("visible") = "false";
		}
		if (image->getZ() != 0.f)
		{
			pugi::xml_node prop = imagelayer.append_child("properties");
			pugi::xml_node pty = prop.append_child("property");
			pty.attribute("name") = "z";
			pty.attribute("value") = image->getZ();
		}
		if (image->getTextureName() != "")
		{
			pugi::xml_node img = imagelayer.append_child("image");
			img.append_attribute("source") = image->getTextureName().c_str();
		}
	}

	doc.save_file(filename.c_str(), " ");
	return true;
}

sf::Vector2i Map::worldToCoords(sf::Vector2f const & world)
{
	return Map::worldToCoords(world, mOrientation, mTileSize, mStaggerIndex, mStaggerAxis, mHexSideLength);
}

sf::Vector2f Map::coordsToWorld(sf::Vector2i const & coords)
{
	return Map::coordsToWorld(coords, mOrientation, mTileSize, mStaggerIndex, mStaggerAxis, mHexSideLength);
}

std::size_t Map::getImageCount()
{
	return mImages.size();
}

std::shared_ptr<SpriteComponent> Map::getImage(std::size_t index)
{
	return mImages[index];
}

void Map::removeImage(std::size_t index)
{
	mImages.erase(mImages.begin() + index);
}

void Map::clearImages()
{
	mImages.clear();
}

Tileset* Map::getTileset()
{
	return mTileset;
}

void Map::setTileset(Tileset * tileset)
{
	mTileset = tileset;
}

std::shared_ptr<LayerComponent> Map::createLayer(std::string const& tilesetName, sf::Vector2i const& size, sf::Vector2i const& tileSize, std::string const& orientation, std::string const& staggerAxis, std::string const& staggerIndex, unsigned int hexSideLength)
{
	std::shared_ptr<LayerComponent> layer = createComponent<LayerComponent>();
	if (layer != nullptr)
	{
		attachComponent(layer);
		layer->create(&getApplication().getResource<Tileset>(tilesetName), size, tileSize, staggerAxis, staggerIndex, orientation, hexSideLength);
	}
	return layer;
}

std::size_t Map::getLayerCount()
{
	return mLayers.size();
}

std::shared_ptr<LayerComponent> Map::getLayer(std::size_t index)
{
	if (0 <= index && index < mLayers.size())
	{
		return mLayers[index];
	}
	return nullptr;
}

std::shared_ptr<LayerComponent> Map::getLayer(std::string const& name)
{
	std::size_t size = mLayers.size();
	for (std::size_t i = 0; i < size; i++)
	{
		if (mLayers[i]->getName() == name)
		{
			return mLayers[i];
		}
	}
	return nullptr;
}

bool Map::hasLayer(std::string const& name)
{
	std::size_t size = mLayers.size();
	for (std::size_t i = 0; i < size; i++)
	{
		if (mLayers[i]->getName() == name)
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
		detachComponent(mLayers[index]);
		removeComponent(mLayers[index]);
		mLayers.erase(mLayers.begin() + index);
	}
}

void Map::removeLayer(std::string const & name)
{
	std::size_t size = mLayers.size();
	for (std::size_t i = 0; i < size; i++)
	{
		if (mLayers[i]->getName() == name)
		{
			detachComponent(mLayers[i]);
			removeComponent(mLayers[i]);
			mLayers.erase(mLayers.begin() + i);
			size--;
			i--;
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
		mLayers[i]->setSize(size);
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
		mLayers[i]->setTileSize(tileSize);
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
		mLayers[i]->setOrientation(orientation);
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
		mLayers[i]->setStaggerAxis(axis);
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
		mLayers[i]->setStaggerIndex(index);
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
		mLayers[i]->setHexSideLength(hexSideLength);
	}
}

} // namespace ke