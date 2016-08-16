#include "LayerComponent.hpp"

LayerComponent::LayerComponent()
	: mVertices()
	, mTexture(nullptr)
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
	: mVertices()
	, mTexture(nullptr)
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
		if (mTexture != nullptr)
		{
			states.texture = mTexture;
		}
	}
	target.draw(mVertices, states);
}

unsigned int LayerComponent::getTileId(sf::Vector2i const& coords)
{
	if (0 <= coords.x && coords.x < mSize.x && 0 <= coords.y && coords.y < mSize.y)
	{
		sf::Vertex* vertex = &mVertices[(coords.x + coords.y * mSize.x) * 6];
		if (vertex[0].texCoords != vertex[2].texCoords && mTileset != nullptr)
		{
			return mTileset->toId(sf::Vector2i(vertex->texCoords.x, vertex->texCoords.y));
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
			sf::Vector2i pos = mTileset->toPos(id);
			vertex[0].texCoords = sf::Vector2f(pos.x, pos.y);
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
		mTexture = &mTileset->getTexture();
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
		for (coords.y = 0; coords.y < mSize.y; coords.y)
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
