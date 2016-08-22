#include "LayerComponent.hpp"

LayerComponent::LayerComponent()
	: mVertices(sf::Triangles)
	, mTileset(nullptr)
	, mSize()
	, mTileSize()
	, mOrientation("orthogonal")
	, mStaggerAxis("y")
	, mStaggerIndex("odd")
	, mHexSideLength(0)
	, mOpacity(1.f)
	, mName()
	, mEncoding()
	, mCompression()
{
	create(nullptr);
}

LayerComponent::LayerComponent(Tileset* tileset, sf::Vector2i const& size, sf::Vector2i const& tileSize, std::string const& orientation, std::string const& staggerAxis, std::string const& staggerIndex, unsigned int hexSideLength)
	: mVertices(sf::Triangles)
	, mTileset(nullptr)
	, mSize()
	, mTileSize()
	, mOrientation("orthogonal")
	, mStaggerAxis("y")
	, mStaggerIndex("odd")
	, mHexSideLength(0)
	, mOpacity(1.f)
	, mName()
	, mEncoding()
	, mCompression()
{
	create(tileset, size, tileSize, orientation, staggerAxis, staggerIndex, hexSideLength);
}

void LayerComponent::render(sf::RenderTarget& target)
{
	sf::RenderStates states;
	states.transform *= getWorldTransform();
	if (mTileset != nullptr)
	{
		states.texture = &mTileset->getTexture();
	}
	target.draw(mVertices, states);
}

bool LayerComponent::loadFromNode(pugi::xml_node const& node, Tileset* tileset, sf::Vector2i const& size, sf::Vector2i const& tileSize, std::string const& orientation, std::string const& staggerAxis, std::string const& staggerIndex, unsigned int hexSideLength)
{
	if (!node)
	{
		return false;
	}
	for (const pugi::xml_attribute& attr : node.attributes())
	{
		if (attr.name() == std::string("name"))
		{
			mName = attr.as_string();
		}
		// TODO : Handle offset as position
		if (attr.name() == std::string("offset"))
		{
		}
		if (attr.name() == std::string("opacity"))
		{
			mOpacity = attr.as_float();
		}
		// TODO : Handle visible
		if (attr.name() == std::string("visible"))
		{
		}
	}

	pugi::xml_node prop = node.child("properties");
	if (prop)
	{
		for (const pugi::xml_node& property : prop.children("property"))
		{
			std::string name = property.attribute("name").as_string();
			std::string value = property.attribute("value").as_string();
			setProperty(name, value);
		}
	}

	pugi::xml_node dataNode = node.child("data");
	if (!dataNode)
	{
		return false;
	}
	for (pugi::xml_attribute attr = dataNode.first_attribute(); attr; attr = attr.next_attribute())
	{
		if (attr.name() == std::string("encoding"))
		{
			mEncoding = attr.as_string();
		}
		if (attr.name() == std::string("compression"))
		{
			mCompression = attr.as_string();
		}
	}

	mTileset = tileset;
	mSize = size;
	mTileSize = tileSize;
	mOrientation = orientation;
	mStaggerAxis = staggerAxis;
	mStaggerIndex = staggerIndex;
	mHexSideLength = hexSideLength;

	updateRender();

	sf::Vector2i coords;
	const unsigned int FLIPPED_HORIZONTALLY_FLAG = 0x80000000;
	const unsigned int FLIPPED_VERTICALLY_FLAG = 0x40000000;
	const unsigned int FLIPPED_DIAGONALLY_FLAG = 0x20000000;
	if (mEncoding == "base64")
	{
		std::string data;
		std::stringstream ss;
		ss << dataNode.text().get();
		ss >> data;
		if (!base64_decode(data))
		{
			return false;
		}
		if (mCompression != "")
		{
			if (!decompressString(data))
			{
				return false;
			}
		}
		std::vector<unsigned char> byteVector;
		byteVector.reserve(mSize.x * mSize.y * 4);
		for (std::string::iterator i = data.begin(); i != data.end(); ++i)
		{
			byteVector.push_back(*i);
		}
		for (std::size_t i = 0; i < byteVector.size() - 3; i += 4)
		{
			unsigned int gid = byteVector[i] | byteVector[i + 1] << 8 | byteVector[i + 2] << 16 | byteVector[i + 3] << 24;
			gid &= ~(FLIPPED_HORIZONTALLY_FLAG | FLIPPED_VERTICALLY_FLAG | FLIPPED_DIAGONALLY_FLAG);
			setTileId(coords, gid);
			coords.x = (coords.x + 1) % mSize.x;
			if (coords.x == 0)
			{
				coords.y++;
			}
		}
	}
	else if (mEncoding == "csv")
	{
		std::string temp(dataNode.text().get());
		std::stringstream data(temp);
		unsigned int gid;
		while (data >> gid)
		{
			if (data.peek() == ',')
			{
				data.ignore();
			}
			gid &= ~(FLIPPED_HORIZONTALLY_FLAG | FLIPPED_VERTICALLY_FLAG | FLIPPED_DIAGONALLY_FLAG);
			setTileId(coords, gid);
			coords.x = (coords.x + 1) % mSize.x;
			if (coords.x == 0)
			{
				coords.y++;
			}
		}
	}
	else
	{
		for (pugi::xml_node tile = dataNode.child("tile"); tile; tile = tile.next_sibling("tile"))
		{
			unsigned int gid = tile.attribute("gid").as_uint();
			gid &= ~(FLIPPED_HORIZONTALLY_FLAG | FLIPPED_VERTICALLY_FLAG | FLIPPED_DIAGONALLY_FLAG);
			setTileId(coords, gid);
			coords.x = (coords.x + 1) % mSize.x;
			if (coords.x == 0)
			{
				coords.y++;
			}
		}
	}

	return true;
}

void LayerComponent::saveToNode(pugi::xml_node & node)
{
	if (!node)
	{
		return;
	}
	if (mName != "")
	{
		node.append_attribute("name") = mName.c_str();
	}
	// TODO : Save offset
	if (mOpacity != 1.f)
	{
		node.append_attribute("opacity") = mOpacity;
	}
	// TODO : Save visibility
	if (mProperties.size() > 0)
	{
		pugi::xml_node properties = node.append_child("properties");
		for (auto itr = mProperties.begin(); itr != mProperties.end(); itr++)
		{
			pugi::xml_node property = properties.append_child("property");
			property.append_attribute("name") = itr->first.c_str();
			property.append_attribute("value") = itr->second.c_str();
		}
	}
	node.append_attribute("width") = mSize.x;
	node.append_attribute("height") = mSize.y;
	pugi::xml_node dataNode = node.append_child("data");
	if (!dataNode)
	{
		return;
	}
	if (mEncoding != "")
	{
		dataNode.append_attribute("encoding") = mEncoding.c_str();
	}
	if (mCompression != "")
	{
		dataNode.append_attribute("compression") = mCompression.c_str();
	}

	std::string data;
	sf::Vector2i coords;
	if (mEncoding == "base64")
	{
		data.reserve(mSize.x * mSize.y * 4);
		for (coords.y = 0; coords.y < mSize.y; coords.y++)
		{
			for (coords.x = 0; coords.x < mSize.x; coords.x++)
			{
				const std::size_t id = getTileId(coords);
				data.push_back((char)(id));
				data.push_back((char)(id >> 8));
				data.push_back((char)(id >> 16));
				data.push_back((char)(id >> 24));
			}
		}
		if (mCompression != "")
		{
			if (!compressString(data))
			{
				return;
			}
		}
		if (!base64_encode(data))
		{
			return;
		}
		std::string out = "\n   " + data + "\n  ";
		dataNode.text().set(out.c_str());
	}
	else if (mEncoding == "csv")
	{
		data += "\n";
		for (coords.y = 0; coords.y < mSize.y; coords.y++)
		{
			for (coords.x = 0; coords.x < mSize.x; coords.x++)
			{
				data += std::to_string(getTileId(coords)) + ",";
			}
			data += "\n";
		}
		if (data.size() > 2)
		{
			data.erase(data.size() - 2);
			data += "\n  ";
		}
		dataNode.text().set(data.c_str());
	}
	else
	{
		for (coords.y = 0; coords.y < mSize.y; coords.y++)
		{
			for (coords.x = 0; coords.x < mSize.x; coords.x++)
			{
				dataNode.append_child("tile").append_attribute("gid") = getTileId(coords);
			}
		}
	}
}

unsigned int LayerComponent::getTileId(sf::Vector2i const& coords)
{
	if (0 <= coords.x && coords.x < mSize.x && 0 <= coords.y && coords.y < mSize.y)
	{
		sf::Vertex* vertex = &mVertices[(coords.x + coords.y * mSize.x) * 6];
		if (vertex[0].texCoords != vertex[2].texCoords && mTileset != nullptr)
		{
			return mTileset->toId(static_cast<sf::Vector2i>(vertex->texCoords));
		}
	}
	return 0;
}

void LayerComponent::setTileId(sf::Vector2i const& coords, unsigned int id)
{
	if (0 <= coords.x && coords.x < mSize.x && 0 <= coords.y && coords.y < mSize.y && id != 0)
	{
		sf::Vertex* vertex = &mVertices[(coords.x + coords.y * mSize.x) * 6];
		if (mTileset != nullptr)
		{
			sf::Vector2f pos = static_cast<sf::Vector2f>(mTileset->toPos(id));
			vertex[0].texCoords = pos;
			vertex[1].texCoords = sf::Vector2f(pos.x + mTileSize.x, pos.y);
			vertex[2].texCoords = sf::Vector2f(pos.x + mTileSize.x, pos.y + mTileSize.y);
			vertex[4].texCoords = sf::Vector2f(pos.x, pos.y + mTileSize.y);
			vertex[3].texCoords = vertex[2].texCoords;
			vertex[5].texCoords = vertex[0].texCoords;
		}
	}
}

std::string LayerComponent::getCode()
{
	std::string data;
	data.reserve(mSize.x * mSize.y * 4);
	sf::Vector2i coords;
	for (coords.y = 0; coords.y < mSize.y; coords.y++)
	{
		for (coords.x = 0; coords.x < mSize.x; coords.x++)
		{
			unsigned int id = getTileId(coords);
			data.push_back((char)(id));
			data.push_back((char)(id >> 8));
			data.push_back((char)(id >> 16));
			data.push_back((char)(id >> 24));
		}
	}
	if (!compress(data))
	{
		return "";
	}
	return data;
}

bool LayerComponent::loadFromCode(std::string const& code)
{
	sf::Vector2i coords;
	std::string data;
	std::stringstream ss;
	ss << code;
	ss >> data;
	if (!decompress(data))
	{
		return false;
	}
	std::vector<unsigned char> byteVector;
	byteVector.reserve(mSize.x * mSize.y * 4);
	for (std::string::iterator i = data.begin(); i != data.end(); ++i)
	{
		byteVector.push_back(*i);
	}
	std::size_t size = byteVector.size();
	for (std::size_t i = 0; i < size - 3; i += 4)
	{
		setTileId(coords, byteVector[i] | byteVector[i + 1] << 8 | byteVector[i + 2] << 16 | byteVector[i + 3] << 24);
		coords.x = (coords.x + 1) % mSize.x;
		if (coords.x == 0)
		{
			coords.y++;
		}
	}
	return true;
}

void LayerComponent::create(Tileset* tileset, sf::Vector2i const& size, sf::Vector2i const& tileSize, std::string const& orientation, std::string const& staggerAxis, std::string const& staggerIndex, unsigned int hexSideLength)
{
	mTileset = tileset;
	mSize = size;
	mTileSize = tileSize;
	mOrientation = orientation;
	mStaggerAxis = staggerAxis;
	mStaggerIndex = staggerIndex;
	mHexSideLength = hexSideLength;

	updateRender();
}

Tileset* LayerComponent::getTileset() const
{
	return mTileset;
}

void LayerComponent::setTileset(Tileset* tileset)
{
	mTileset = tileset;
	if (mTileset != nullptr)
	{
		updateRender();
	}
}

float LayerComponent::getOpacity() const
{
	return mOpacity;
}

void LayerComponent::setOpacity(float opacity)
{
	mOpacity = opacity;
	sf::Color color = sf::Color(255, 255, 255, static_cast<unsigned char>(255.f * mOpacity));
	std::size_t size = mVertices.getVertexCount();
	for (std::size_t i = 0; i < size; i++)
	{
		mVertices[i].color = color;
	}
}

std::string LayerComponent::getName() const
{
	return mName;
}

void LayerComponent::setName(std::string const& name)
{
	mName = name;
}

const std::string& LayerComponent::getEncoding() const
{
	return mEncoding;
}

void LayerComponent::setEncoding(std::string const& encoding)
{
	mEncoding = encoding;
}

const std::string& LayerComponent::getCompression() const
{
	return mCompression;
}

void LayerComponent::setCompression(std::string const& compression)
{
	mCompression = compression;
}

const sf::Vector2i& LayerComponent::getSize() const
{
	return mSize;
}

void LayerComponent::setSize(sf::Vector2i const& size)
{
	mSize = size;
	if (mSize != sf::Vector2i())
	{
		updateRender();
	}
}

const sf::Vector2i& LayerComponent::getTileSize() const
{
	return mTileSize;
}

void LayerComponent::setTileSize(sf::Vector2i const& tileSize)
{
	mTileSize = tileSize;
	if (mTileSize != sf::Vector2i())
	{
		updateRender();
	}
}

const std::string& LayerComponent::getOrientation() const
{
	return mOrientation;
}

void LayerComponent::setOrientation(std::string const& orientation)
{
	mOrientation = orientation;
	if (mOrientation != "")
	{
		updateRender();
	}
}

const std::string& LayerComponent::getStaggerAxis() const
{
	return mStaggerAxis;
}

void LayerComponent::setStaggerAxis(std::string const& axis)
{
	mStaggerAxis = axis;
	if (mStaggerAxis != "" && (mOrientation == "hexagonal" || mOrientation == "staggered"))
	{
		updateRender();
	}
}

const std::string& LayerComponent::getStaggerIndex() const
{
	return mStaggerIndex;
}

void LayerComponent::setStaggerIndex(std::string const& index)
{
	mStaggerIndex = index;
	if (mStaggerIndex != "" && (mOrientation == "hexagonal" || mOrientation == "staggered"))
	{
		updateRender();
	}
}

unsigned int LayerComponent::getHexSizeLength() const
{
	return mHexSideLength;
}

void LayerComponent::setHexSideLength(unsigned int hexSideLength)
{
	mHexSideLength = hexSideLength;
	if (mHexSideLength != 0 && mOrientation == "hexagonal")
	{
		updateRender();
	}
}

void LayerComponent::updateRender()
{
	if (mTileset == nullptr || mSize.x == 0 || mSize.y == 0 || mTileSize.x == 0 || mTileSize.y == 0)
	{
		return;
	}
	sf::Vector2f texSize = static_cast<sf::Vector2f>(mTileset->getTileSize());
	sf::Color color = sf::Color(255, 255, 255, static_cast<unsigned char>(255.f * mOpacity));
	mVertices.resize(mSize.x * mSize.y * 6);
	sf::Vector2i coords;
	for (coords.x = 0; coords.x < mSize.x; coords.x++)
	{
		for (coords.y = 0; coords.y < mSize.y; coords.y++)
		{
			sf::Vector2f pos = getVertexPosition(coords);
			sf::Vertex* vertex = &mVertices[(coords.x + coords.y * mSize.x) * 6];
			vertex[0].position = pos;
			vertex[1].position = sf::Vector2f(pos.x + texSize.x, pos.y);
			vertex[2].position = sf::Vector2f(pos.x + texSize.x, pos.y + texSize.y);
			vertex[4].position = sf::Vector2f(pos.x, pos.y + texSize.y);
			vertex[3].position = vertex[2].position;
			vertex[5].position = vertex[0].position;
			for (std::size_t i = 0; i < 6; i++)
			{
				vertex[i].color = color;
			}
		}
	}
}

sf::Vector2f LayerComponent::getVertexPosition(sf::Vector2i const & coords)
{
	sf::Vector2f pos;
	unsigned int index = (mStaggerIndex == "odd") ? 0 : 1;
	if (mOrientation == "orthogonal")
	{
		pos.x = static_cast<float>(coords.x * mTileSize.x);
		pos.y = static_cast<float>(coords.y * mTileSize.y);
	}
	else if (mOrientation == "isometric")
	{
		pos.x = ((float)coords.x - (float)coords.y) * mTileSize.x * 0.5f;
		pos.y = ((float)coords.x + (float)coords.y) * mTileSize.y * 0.5f;
	}
	else if (mOrientation == "staggered")
	{
		if (mStaggerAxis == "y")
		{
			if ((coords.y % 2) == index)
			{
				pos.x = static_cast<float>(coords.x * mTileSize.x);
			}
			else
			{
				pos.x = static_cast<float>((coords.x + 0.5f) * mTileSize.x);
			}
			pos.y = coords.y * mTileSize.y * 0.5f;
		}
		else
		{
			if ((coords.x % 2) == index)
			{
				pos.y = static_cast<float>(coords.y * mTileSize.y);
			}
			else
			{
				pos.y = static_cast<float>((coords.y + 0.5f) * mTileSize.y);
			}
			pos.x = coords.x * mTileSize.x * 0.5f;
		}
	}
	else if (mOrientation == "hexagonal")
	{
		if (mStaggerAxis == "y")
		{
			if ((coords.y % 2) == index)
			{
				pos.x = static_cast<float>(coords.x * mTileSize.x);
			}
			else
			{
				pos.x = static_cast<float>((coords.x + 0.5f) * mTileSize.x);
			}
			pos.y = coords.y * ((mTileSize.y - mHexSideLength) * 0.5f + mHexSideLength);
		}
		else
		{
			if ((coords.x % 2) == index)
			{
				pos.y = static_cast<float>(coords.y * mTileSize.y);
			}
			else
			{
				pos.y = static_cast<float>((coords.y + 0.5f) * mTileSize.y);
			}
			pos.x = coords.x * ((mTileSize.x - mHexSideLength) * 0.5f + mHexSideLength);
		}
	}
	return pos;
}
