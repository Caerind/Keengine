#include "ResourceManager.hpp"
#include "../System/Log.hpp"

Resource::Resource()
{ 
	mLoaded = false; 
}

Resource::~Resource()
{
}

bool Resource::isLoaded() const
{ 
	return mLoaded; 
}

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
	releaseAllResources();
}

bool ResourceManager::hasResource(std::string const& id) const
{
	auto itr = mResources.find(id);
	return (itr != mResources.end() && itr->second != nullptr);
}

bool ResourceManager::isResourceLoaded(std::string const& id) const
{
	return (hasResource(id) && mResources.find(id)->second->isLoaded());
}

void ResourceManager::releaseResource(std::string const& id)
{
	if (mResources.find(id) != mResources.end())
	{
		delete mResources[id];
		mResources.erase(mResources.find(id));
	}
}

void ResourceManager::releaseAllResources()
{
	for (auto itr = mResources.begin(); itr != mResources.end(); itr++)
	{
		delete itr->second;
	}
	mResources.clear();
}

Texture::Texture() 
{
}

Texture::Texture(std::string const& filename)
{ 
	loadFromFile(filename); 
}

bool Texture::loadFromFile(std::string const& filename, sf::IntRect const& area)
{
	bool r = sf::Texture::loadFromFile(filename, area); 
	mLoaded = r;
	return r; 

}
bool Texture::loadFromMemory(void const* data, std::size_t size, sf::IntRect const& area)
{ 
	bool r = sf::Texture::loadFromMemory(data, size, area); 
	mLoaded = r; 
	return r; 
}

bool Texture::loadFromStream(sf::InputStream& stream, sf::IntRect const& area)
{ 
	bool r = sf::Texture::loadFromStream(stream, area); 
	mLoaded = r;
	return r; 
}

bool Texture::loadFromImage(sf::Image const& image, sf::IntRect const& area)
{ 
	bool r = sf::Texture::loadFromImage(image, area); 
	mLoaded = r; 
	return r; 
}

Image::Image() 
{
}

Image::Image(std::string const& filename)
{ 
	loadFromFile(filename); 
}

bool Image::loadFromFile(std::string const& filename)
{ 
	bool r = sf::Image::loadFromFile(filename); 
	mLoaded = r; 
	return r; 
}

bool Image::loadFromMemory(void const* data, std::size_t size)
{ 
	bool r = sf::Image::loadFromMemory(data, size); 
	mLoaded = r; 
	return r; 
}

bool Image::loadFromStream(sf::InputStream& stream)
{ 
	bool r = sf::Image::loadFromStream(stream);
	mLoaded = r; 
	return r; }

Font::Font() 
{
}

Font::Font(std::string const& filename)
{ 
	loadFromFile(filename); 
}

bool Font::loadFromFile(std::string const& filename)
{ 
	bool r = sf::Font::loadFromFile(filename);
	mLoaded = r; 
	return r; 
}

bool Font::loadFromMemory(void const* data, std::size_t size)
{ 
	bool r = sf::Font::loadFromMemory(data, size); 
	mLoaded = r; 
	return r; 
}

bool Font::loadFromStream(sf::InputStream& stream)
{
	bool r = sf::Font::loadFromStream(stream); 
	mLoaded = r; 
	return r; 
}

SoundBuffer::SoundBuffer() 
{
}

SoundBuffer::SoundBuffer(std::string const& filename)
{ 
	loadFromFile(filename); 
}

bool SoundBuffer::loadFromFile(std::string const& filename)
{ 
	bool r = sf::SoundBuffer::loadFromFile(filename); 
	mLoaded = r; 
	return r; 
}

bool SoundBuffer::loadFromMemory(void const* data, std::size_t size)
{ 
	bool r = sf::SoundBuffer::loadFromMemory(data, size); 
	mLoaded = r; 
	return r; 
}

bool SoundBuffer::loadFromStream(sf::InputStream& stream)
{ 
	bool r = sf::SoundBuffer::loadFromStream(stream); 
	mLoaded = r; 
	return r; 
}

bool SoundBuffer::loadFromSamples(sf::Int16 const* samples, sf::Uint64 sampleCount, unsigned int channelCount, unsigned int sampleRate)
{ 
	bool r = sf::SoundBuffer::loadFromSamples(samples, sampleCount, channelCount, sampleRate); 
	mLoaded = r; 
	return r; 
}

Shader::Shader() 
{
}

bool Shader::loadFromFile(std::string const& filename, sf::Shader::Type type)
{ 
	bool r = sf::Shader::loadFromFile(filename, type); 
	mLoaded = r;
	return r; 
}

bool Shader::loadFromFile(std::string const& vertexShaderFilename, std::string const& fragmentShaderFilename)
{ 
	bool r = sf::Shader::loadFromFile(vertexShaderFilename, fragmentShaderFilename); 
	mLoaded = r; 
	return r; 
}

bool Shader::loadFromMemory(std::string const& shader, sf::Shader::Type type)
{ 
	bool r = sf::Shader::loadFromMemory(shader, type); 
	mLoaded = r; 
	return r; 
}

bool Shader::loadFromMemory(std::string const& vertexShader, std::string const& fragmentShader)
{ 
	bool r = sf::Shader::loadFromMemory(vertexShader, fragmentShader); 
	mLoaded = r;
	return r; 
}

bool Shader::loadFromStream(sf::InputStream& stream, sf::Shader::Type type)
{ 
	bool r = sf::Shader::loadFromStream(stream, type);
	mLoaded = r; 
	return r; 
}

bool Shader::loadFromStream(sf::InputStream& vertexShaderStream, sf::InputStream& fragmentShaderStream)
{
	bool r = sf::Shader::loadFromStream(vertexShaderStream, fragmentShaderStream); 
	mLoaded = r; 
	return r; 
}

void Shader::setUniform(std::string const& name, float x)
{
	sf::Shader::setParameter(name, x);
	mFloats[name] = x;
}

float Shader::getUniformFloat(std::string const& name)
{
	return mFloats[name];
}

void Shader::setUniform(std::string const& name, sf::Vector2f const& vector)
{
	sf::Shader::setParameter(name, vector);
	mVectors2f[name] = vector;
}

sf::Vector2f Shader::getUniformVector2f(std::string const& name)
{
	return mVectors2f[name];
}

void Shader::setUniform(std::string const& name, sf::Vector3f const& vector)
{
	sf::Shader::setParameter(name, vector);
	mVectors3f[name] = vector;
}

sf::Vector3f Shader::getUniformVector3f(std::string const& name)
{
	return mVectors3f[name];
}

void Shader::setUniform(std::string const& name, sf::Color const& color)
{
	sf::Shader::setParameter(name, color);
	mColors[name] = color;
}

sf::Color Shader::getUniformColor(std::string const& name)
{
	return mColors[name];
}

Theme::Theme()
{
}

Theme::Theme(std::string const& filename)
{ 
	loadFromFile(filename); 
}

bool Theme::loadFromFile(std::string const& filename)
{
	mTheme = std::make_shared<tgui::Theme>(filename);
	mLoaded = (mTheme != nullptr);
	return mLoaded;
}

tgui::WidgetConverter Theme::create(std::string const& className)
{
	return mTheme->load(className);
}

Tileset::Tileset()
	: mFirstGid(1)
	, mSource()
	, mName()
	, mTileSize()
	, mSpacing(0)
	, mMargin(0)
	, mTileCount(0)
	, mColumns(0)
	, mTileOffset()
	, mImageData()
	, mImageFormat()
	, mImageSource()
	, mImageTransparent(sf::Color::Transparent)
	, mImageSize()
	, mImageChanged(true)
	, mMapPath("")
{
}

Tileset::Tileset(pugi::xml_node const& node, std::string const& mapPath)
	: mFirstGid(1)
	, mSource()
	, mName()
	, mTileSize()
	, mSpacing(0)
	, mMargin(0)
	, mTileCount(0)
	, mColumns(0)
	, mTileOffset()
	, mImageData()
	, mImageFormat()
	, mImageSource()
	, mImageTransparent(sf::Color::Transparent)
	, mImageSize()
	, mImageChanged(true)
	, mMapPath("")
{
	loadFromNode(node, mapPath);
}

bool Tileset::loadFromNode(pugi::xml_node const& node, std::string const& mapPath, bool fromTsx)
{
	mMapPath = mapPath;
	for (const pugi::xml_attribute& attr : node.attributes())
	{
		if (attr.name() == std::string("firstgid"))
		{
			mFirstGid = attr.as_uint();
		}
		if (attr.name() == std::string("source"))
		{
			mSource = attr.as_string();
		}
		if (attr.name() == std::string("name"))
		{
			mName = attr.as_string();
		}
		if (attr.name() == std::string("tilewidth"))
		{
			mTileSize.x = attr.as_int();
		}
		if (attr.name() == std::string("tileheight"))
		{
			mTileSize.y = attr.as_int();
		}
		if (attr.name() == std::string("spacing"))
		{
			mSpacing = attr.as_uint();
		}
		if (attr.name() == std::string("margin"))
		{
			mMargin = attr.as_uint();
		}
		if (attr.name() == std::string("tilecount"))
		{
			mTileCount = attr.as_uint();
		}
		if (attr.name() == std::string("columns"))
		{
			mColumns = attr.as_uint();
		}
	}

	if (mSource != "" && !fromTsx)
	{
		return loadFromFile(mMapPath + mSource);
	}

	// TODO : Handle offset

	pugi::xml_node image = node.child("image");
	if (image)
	{
		for (const pugi::xml_attribute& attr : image.attributes())
		{
			if (attr.name() == std::string("format"))
			{
				mImageFormat = attr.as_string();
			}
			if (attr.name() == std::string("source"))
			{
				mImageSource = attr.as_string();
			}
			if (attr.name() == std::string("trans"))
			{
				std::string color = attr.as_string();
				if (color != "")
				{
					if (color[0] == '#')
					{
						color.erase(color.begin());
					}
					int hexTrans;
					std::stringstream ss(color);
					ss >> std::hex >> hexTrans;
					if (hexTrans >= 0)
					{
						unsigned char red, green, blue;
						red = hexTrans >> 16;
						green = (hexTrans >> 8) & 0xff;
						blue = hexTrans & 0xff;
						mImageTransparent = sf::Color(red, green, blue);
					}
				}
			}
			if (attr.name() == std::string("width"))
			{
				mImageSize.x = attr.as_uint();
			}
			if (attr.name() == std::string("height"))
			{
				mImageSize.y = attr.as_uint();
			}
		}
		pugi::xml_node data = image.child("data");
		if (data)
		{
			std::stringstream ss(data.text().get());
			ss >> mImageData;
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

	getTexture();

	mLoaded = true;
	return true;
}

bool Tileset::loadFromFile(std::string const& filename)
{
	mLoaded = false;
	if (filename == "")
	{
		return false;
	}
	pugi::xml_document doc;
	if (!doc.load_file(filename.c_str()))
	{
		return false;
	}
	pugi::xml_node tileset = doc.child("tileset");
	if (!tileset)
	{
		return false;
	}
	return loadFromNode(tileset, mMapPath, true);
}

bool Tileset::saveToNode(pugi::xml_node& node, bool fromTsx)
{
	if (!fromTsx)
	{
		node.append_attribute("firstgid") = mFirstGid;
	}
	if (mSource != "" && !fromTsx)
	{
		node.append_attribute("source") = mSource.c_str();
		return saveToFile(mMapPath + mSource);
	}
	node.append_attribute("name") = mName.c_str();
	node.append_attribute("tilewidth") = mTileSize.x;
	node.append_attribute("tileheight") = mTileSize.y;
	if (mSpacing != 0)
	{
		node.append_attribute("spacing") = mSpacing;
	}
	if (mMargin != 0)
	{
		node.append_attribute("margin") = mMargin;
	}
	node.append_attribute("tilecount") = mTileCount;
	node.append_attribute("columns") = mColumns;

	// TODO : Save Offset

	pugi::xml_node image = node.append_child("image");
	if (mImageFormat != "")
	{
		image.append_attribute("format") = mImageFormat.c_str();
	}
	if (mImageSource != "")
	{
		image.append_attribute("source") = mImageSource.c_str();
	}
	if (mImageTransparent != sf::Color::Transparent)
	{
		std::ostringstream oss;
		oss << "#" << std::hex << mImageTransparent.toInteger();
		image.append_attribute("trans") = oss.str().c_str();
	}
	if (mImageSize != sf::Vector2i())
	{
		image.append_attribute("width") = mImageSize.x;
		image.append_attribute("height") = mImageSize.y;
	}
	if (mImageData != "")
	{
		pugi::xml_node data = image.append_child("data");
		data.text().set(mImageData.data());
	}

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

	return true;
}

bool Tileset::saveToFile(std::string const& filename)
{
	if (filename == "")
	{
		return false;
	}
	pugi::xml_document doc;
	pugi::xml_node tileset = doc.append_child("tileset");
	if (!saveToNode(tileset, true))
	{
		return false;
	}
	if (!doc.save_file(filename.c_str()))
	{
		return false;
	}
	return true;
}

unsigned int Tileset::getFirstGid() const
{
	return mFirstGid;
}

const std::string& Tileset::getSource() const
{
	return mSource;
}

const std::string& Tileset::getName() const
{
	return mName;
}

const sf::Vector2i& Tileset::getTileSize() const
{
	return mTileSize;
}

unsigned int Tileset::getSpacing() const
{
	return mSpacing;
}

unsigned int Tileset::getMargin() const
{
	return mMargin;
}

unsigned int Tileset::getTileCount() const
{
	return mTileCount;
}

unsigned int Tileset::getColumns() const
{
	return mColumns;
}

const sf::Vector2f& Tileset::getTileOffset() const
{
	return mTileOffset;
}

const std::string& Tileset::getImageData() const
{
	return mImageData;
}

const std::string& Tileset::getImageFormat() const
{
	return mImageFormat;
}

const std::string& Tileset::getImageSource() const
{
	return mImageSource;
}

sf::Color Tileset::getImageTransparent() const
{
	return mImageTransparent;
}

const sf::Vector2i& Tileset::getImageSize() const
{
	return mImageSize;
}

void Tileset::setFirstGid(unsigned int id)
{
	mFirstGid = id;
}

void Tileset::setSource(std::string const& source)
{
	mSource = source;
}

void Tileset::setName(std::string const& name)
{
	mName = name;
}

void Tileset::setTileSize(sf::Vector2i const& tileSize)
{
	mTileSize = tileSize;
}

void Tileset::setSpacing(unsigned int spacing)
{
	mSpacing = spacing;
}

void Tileset::setMargin(unsigned int margin)
{
	mMargin = margin;
}

void Tileset::setTileCount(unsigned int tileCount)
{
	mTileCount = tileCount;
}

void Tileset::setColumns(unsigned int columns)
{
	mColumns = columns;
}

void Tileset::setOffset(sf::Vector2f const& offset)
{
	mTileOffset = offset;
}

void Tileset::setImageData(std::string const& data)
{
	if (mImageData != data)
	{
		mImageChanged = true;
	}
	mImageData = data;
}

void Tileset::setImageFormat(std::string const& format)
{
	mImageFormat = format;
}

void Tileset::setImageSource(std::string const& source)
{
	if (mImageSource != source)
	{
		mImageChanged = true;
	}
	mImageSource = source;
}

void Tileset::setImageTransparent(sf::Color const& color)
{
	if (mImageTransparent != color)
	{
		mImageChanged = true;
	}
	mImageTransparent = color;
}

void Tileset::setImageSize(sf::Vector2i const& size)
{
	mImageSize = size;
}

sf::Texture& Tileset::getTexture()
{
	if (mImageChanged)
	{
		if (mImageTransparent != sf::Color::Transparent)
		{
			sf::Image image;
			if (mImageSource != "")
			{
				image.loadFromFile(mMapPath + mImageSource);
			}
			else if (mImageData != "")
			{
				image.loadFromMemory(mImageData.data(), mImageData.size());
			}

			image.createMaskFromColor(mImageTransparent);

			mTexture.loadFromImage(image);
		}
		else
		{
			if (mImageSource != "")
			{
				mTexture.loadFromFile(mMapPath + mImageSource);
			}
			else if (mImageData != "")
			{
				mTexture.loadFromMemory(mImageData.data(), mImageData.size());
			}
		}
		mImageChanged = false;
	}
	return mTexture;
}

sf::Vector2i Tileset::toPos(unsigned int gid)
{
	if (gid < mFirstGid || gid >= mFirstGid + mTileCount)
	{
		return sf::Vector2i();
	}

	gid -= mFirstGid; // Local id
	sf::Vector2i pos;
	if (mColumns > 0) // Avoid div 0
	{
		pos.x = (gid % mColumns) * (mTileSize.x + mSpacing) + mMargin;
		pos.y = (gid / mColumns) * (mTileSize.y + mSpacing) + mMargin;
	}
	return pos;
}

sf::IntRect Tileset::toRect(unsigned int gid)
{
	if (gid < mFirstGid || gid >= mFirstGid + mTileCount)
	{
		return sf::IntRect();
	}

	gid -= mFirstGid;
	sf::IntRect rect;
	if (mColumns > 0) // Avoid div 0
	{
		rect.left = (gid % mColumns) * (mTileSize.x + mSpacing) + mMargin;
		rect.top = (gid / mColumns) * (mTileSize.y + mSpacing) + mMargin;
		rect.width = mTileSize.x;
		rect.height = mTileSize.y;
	}
	return rect;
}

unsigned int Tileset::toId(sf::Vector2i const& pos)
{
	if (mTileSize != sf::Vector2i())
	{
		return 1 + (pos.x - mMargin) / (mTileSize.x + mSpacing) + (pos.y - mMargin) / (mTileSize.y + mSpacing) * mColumns;
	}
	return 0;
}