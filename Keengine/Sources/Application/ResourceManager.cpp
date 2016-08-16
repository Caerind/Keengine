#include "ResourceManager.hpp"
#include "Application.hpp"

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
	, mTexture()
{
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
	mImageData = data;
}

void Tileset::setImageFormat(std::string const& format)
{
	mImageFormat = format;
}

void Tileset::setImageSource(std::string const& source)
{
	mImageSource = source;
}

void Tileset::setImageTransparent(sf::Color const& color)
{
	mImageTransparent = color;
}

void Tileset::setImageSize(sf::Vector2i const& size)
{
	mImageSize = size;
}

sf::Texture& Tileset::getTexture()
{
	return Application::getResource<Texture>(mSource);
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