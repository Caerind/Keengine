#include "ResourceManager.hpp"
#include "../System/Log.hpp"

namespace ke
{

Resource::Resource()
{ 
	mLoaded = false; 
}

Resource::~Resource()
{
}

void Resource::setLoaded(bool loaded)
{
	mLoaded = loaded;
}

bool Resource::isLoaded() const
{ 
	return mLoaded; 
}

void Resource::setName(const std::string& name)
{
	mName = name;
}

const std::string& Resource::getName() const
{
	return mName;
}

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
	releaseAllResources();
}

bool ResourceManager::hasResource(const std::string& id) const
{
	std::size_t size = mResources.size();
	for (std::size_t i = 0; i < size; i++)
	{
		if (mResources.at(i) != nullptr && mResources.at(i)->getName() == id)
		{
			return true;
		}
	}
	return false;
}

bool ResourceManager::isResourceLoaded(const std::string& id) const
{
	std::size_t size = mResources.size();
	for (std::size_t i = 0; i < size; i++)
	{
		if (mResources.at(i) != nullptr && mResources.at(i)->getName() == id && mResources.at(i)->isLoaded())
		{
			return true;
		}
	}
	return false;
}

void ResourceManager::releaseResource(const std::string& id)
{
	std::size_t size = mResources.size();
	for (std::size_t i = 0; i < size; i++)
	{
		if (mResources[i] == nullptr)
		{
			mResources.erase(mResources.begin() + i);
			i--;
			size--;
		}
		else if (mResources[i]->getName() == id)
		{
			delete mResources[i];
			mResources[i] = nullptr;
			mResources.erase(mResources.begin() + i);
			i--;
			size--;
		}
	}
}

void ResourceManager::releaseAllResources()
{
	std::size_t size = mResources.size();
	for (std::size_t i = 0; i < size; i++)
	{
		if (mResources[i] != nullptr)
		{
			delete mResources[i];
			mResources[i] = nullptr;
		}
	}
	mResources.clear();
}

bool ResourceManager::loadResources(const std::string& filename)
{
	pugi::xml_document doc;
	std::ifstream file(filename);
	if (!file)
	{
		return false;
	}
	doc.load(file);
	pugi::xml_node root = doc.child("Resources");

	for (pugi::xml_node node : root.children("Texture"))
	{
		createResource<Texture>(node.attribute("name").as_string(), node.attribute("filename").as_string());
	}
	for (pugi::xml_node node : root.children("Image"))
	{
		createResource<Image>(node.attribute("name").as_string(), node.attribute("filename").as_string());
	}
	for (pugi::xml_node node : root.children("Font"))
	{
		createResource<Font>(node.attribute("name").as_string(), node.attribute("filename").as_string());
	}
	for (pugi::xml_node node : root.children("SoundBuffer"))
	{
		createResource<SoundBuffer>(node.attribute("name").as_string(), node.attribute("filename").as_string());
	}
	for (pugi::xml_node node : root.children("Shader"))
	{
		std::string name = node.attribute("name").as_string();
		if (node.attribute("type") && node.attribute("filename"))
		{
			createResource<Shader>(name, node.attribute("filename").as_string(), static_cast<sf::Shader::Type>(node.attribute("type").as_uint()));
		}
		else
		{
			createResource<Shader>(name, node.attribute("vertex").as_string(), node.attribute("fragment").as_string());
		}
	}
	for (pugi::xml_node node : root.children("Theme"))
	{
		createResource<Theme>(node.attribute("name").as_string(), node.attribute("filename").as_string());
	}
	for (pugi::xml_node node : root.children("Lang"))
	{
		Lang& lang = createResource<Lang>(node.attribute("name").as_string());
		for (pugi::xml_node token = doc.child("Token"); token; token = token.next_sibling("Token"))
		{
			lang.add(token.attribute("name").as_string(), token.text().get());
		}
		lang.setLoaded(true);
	}
	for (pugi::xml_node node : root.children("Animation"))
	{
		Animation& animation = createResource<Animation>(node.attribute("name").as_string());
		for (pugi::xml_node frame : node.children("Frame"))
		{
			std::string textureName = frame.attribute("textureName").as_string();
			sf::IntRect textureRect = fromString<sf::IntRect>(frame.attribute("textureRect").as_string());
			sf::Time duration = fromString<sf::Time>(frame.attribute("duration").as_string());
			animation.addFrame(textureName, textureRect, duration);
		}
		animation.setLoaded(true);
	}

	return true;
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

Shader::Shader(std::string const& filename, sf::Shader::Type type)
{
	loadFromFile(filename, type);
}

Shader::Shader(std::string const& vertexShaderFilename, std::string const& fragmentShaderFilename)
{
	loadFromFile(vertexShaderFilename, fragmentShaderFilename);
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
	sf::Shader::setUniform(name, x);
	mFloats[name] = x;
}

float Shader::getUniformFloat(std::string const& name)
{
	return mFloats[name];
}

void Shader::setUniform(std::string const& name, sf::Vector2f const& vector)
{
	sf::Shader::setUniform(name, vector);
	mVectors2f[name] = vector;
}

sf::Vector2f Shader::getUniformVector2f(std::string const& name)
{
	return mVectors2f[name];
}

void Shader::setUniform(std::string const& name, sf::Vector3f const& vector)
{
	sf::Shader::setUniform(name, vector);
	mVectors3f[name] = vector;
}

sf::Vector3f Shader::getUniformVector3f(std::string const& name)
{
	return mVectors3f[name];
}

void Shader::setUniform(std::string const& name, sf::Color const& color)
{
	sf::Shader::setUniform(name, sf::Glsl::Vec4(color));
	mColors[name] = color;
}

sf::Color Shader::getUniformColor(std::string const& name)
{
	return mColors[name];
}

void Shader::setUniform(std::string const& name, sf::Texture const& texture)
{
	sf::Shader::setUniform(name, texture);
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
	: mMapPath("")
	, mFirstGid(1)
	, mTileSize()
	, mSpacing(0)
	, mMargin(0)
	, mTileCount(0)
	, mColumns(0)
	, mImageSource()
	, mImageTransparent(sf::Color::Transparent)
	, mImageChanged(true)
{
}

Tileset::Tileset(pugi::xml_node const& node, std::string const& mapPath)
	: mMapPath("")
	, mFirstGid(1)
	, mTileSize()
	, mSpacing(0)
	, mMargin(0)
	, mTileCount(0)
	, mColumns(0)
	, mImageSource()
	, mImageTransparent(sf::Color::Transparent)
	, mImageChanged(true)
{
	loadFromNode(node, mapPath);
}

bool Tileset::loadFromNode(pugi::xml_node const& node, std::string const& mapPath)
{
	mMapPath = mapPath;
	for (const pugi::xml_attribute& attr : node.attributes())
	{
		if (attr.name() == std::string("firstgid"))
		{
			mFirstGid = attr.as_uint();
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

	pugi::xml_node image = node.child("image");
	if (image)
	{
		for (const pugi::xml_attribute& attr : image.attributes())
		{
			if (attr.name() == std::string("source"))
			{
				mImageSource = attr.as_string();
			}
			if (attr.name() == std::string("trans"))
			{
				mImageTransparent = fromString<sf::Color>(attr.as_string());
			}
		}
	}

	PropertiesHolder::loadFromXml(node);

	mImageChanged = true;
	getTexture();

	mLoaded = true;
	return true;
}

bool Tileset::saveToNode(pugi::xml_node& node)
{
	node.append_attribute("firstgid") = mFirstGid;
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

	pugi::xml_node image = node.append_child("image");
	if (mImageSource != "")
	{
		image.append_attribute("source") = mImageSource.c_str();
	}
	if (mImageTransparent != sf::Color::Transparent)
	{
		image.append_attribute("trans") = toString(mImageTransparent).c_str();
	}

	PropertiesHolder::saveToXml(node);

	return true;
}

unsigned int Tileset::getFirstGid() const
{
	return mFirstGid;
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

const std::string& Tileset::getImageSource() const
{
	return mImageSource;
}

sf::Color Tileset::getImageTransparent() const
{
	return mImageTransparent;
}

void Tileset::setFirstGid(unsigned int id)
{
	mFirstGid = id;
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

sf::Texture& Tileset::getTexture()
{
	if (mImageChanged)
	{
		sf::Image image;
		image.loadFromFile(mMapPath + mImageSource);
		image.createMaskFromColor(mImageTransparent);
		mTexture.loadFromImage(image);
		mImageChanged = false;
	}
	return mTexture;
}

bool Tileset::possess(unsigned int gid)
{
	return (mFirstGid <= gid && gid < mFirstGid + mTileCount);
}

sf::Vector2i Tileset::toPos(unsigned int gid)
{
	if (!possess(gid))
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
	if (!possess(gid))
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

Lang::Lang()
{
}

void Lang::add(const std::string& id, const std::string& value)
{
	mLang[id] = value;
}

IniParser::IniParser(std::string const& filename)
{
	loadFromFile(filename);
}

bool IniParser::loadFromFile(std::string const & filename)
{
	std::ifstream file(filename);
	if (!file)
	{
		return false;
	}
	auto trim = [](std::string line)
	{
		while (line.size() && (line.back() == '\t' || line.back() == ' ')) line.pop_back();
		while (line.size() && (line.front() == '\t' || line.front() == ' ')) line = line.substr(1);
		return line;
	};
	std::string line;
	while (std::getline(file, line))
	{
		line = trim(line);
		if (line.size() >= 1 && line.front() != ';')
		{
			std::size_t found = line.find_first_of('=');
			std::string key = trim(line.substr(0, found));
			std::string value = (found == std::string::npos) ? std::string() : trim(line.substr(found + 1));
			mPairs.push_back(std::pair<std::string, Variant>(key, value));
		}
	}
	mLoaded = true;
	return true;
}

bool IniParser::saveToFile(std::string const & filename) const
{
	std::ofstream file(filename);
	if (!file)
	{
		return false;
	}
	for (std::size_t i = 0; i < mPairs.size(); i++)
	{
		file << mPairs[i].first << "=" << mPairs[i].second << std::endl;
	}
	file.close();
	return true;
}

Animation::Animation()
{
}

void Animation::addFrame(Animation::Frame const& frame)
{
	mFrames.push_back(frame);
}

void Animation::addFrame(std::string const& textureName, sf::IntRect const& textureRect, sf::Time duration)
{
	Animation::Frame frame;
	frame.textureName = textureName;
	frame.textureRect = textureRect;
	frame.duration = duration;
	addFrame(frame);
}

std::size_t Animation::getFrameCount() const
{
	return mFrames.size();
}

Animation::Frame& Animation::getFrame(std::size_t index)
{
	return mFrames.at(index);
}

void Animation::removeFrame(std::size_t index)
{
	mFrames.erase(mFrames.begin() + index);
}

void Animation::removeAllFrames()
{
	mFrames.clear();
}

sf::Time Animation::getDuration() const
{
	sf::Time duration;
	for (const auto& f : mFrames)
	{
		duration += f.duration;
	}
	return duration;
}

} // namespace ke