#ifndef KE_RESOURCEMANAGER_HPP
#define KE_RESOURCEMANAGER_HPP

#include <cassert>
#include <iostream>
#include <map>
#include <string>

#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <TGUI/Loading/Theme.hpp>

#include "PropertiesHolder.hpp"
#include "../System/Log.hpp"
#include "../ExtLibs/pugixml.hpp"

namespace ke
{

class Resource
{
    public:
		Resource();
		virtual ~Resource();

		void setLoaded(bool loaded);
		bool isLoaded() const;

		void setName(const std::string& name);
		const std::string& getName() const;

    protected:
        bool mLoaded;
		std::string mName;
};

class ResourceManager
{
    public:
		ResourceManager();

		~ResourceManager();

        template <typename T, typename ... Args>
        T& createResource(const std::string& id, Args&& ... args)
        {
			std::size_t size = mResources.size();
			for (std::size_t i = 0; i < size; i++)
			{
				if (mResources[i] != nullptr && mResources[i]->getName() == id)
				{
					return *dynamic_cast<T*>(mResources[i]);
				}
			}
            mResources.push_back(new T(std::forward<Args>(args)...));
			mResources.back()->setName(id);
            return *dynamic_cast<T*>(mResources.back());
        }

        template <typename T>
        T& getResource(const std::string& id)
        {
			std::size_t size = mResources.size();
			for (std::size_t i = 0; i < size; i++)
			{
				if (mResources[i] != nullptr && mResources[i]->getName() == id)
				{
					return *dynamic_cast<T*>(mResources[i]);
				}
			}
            Log::instance() << Log::Error << std::string("Resource with id (" + id + ") wasn't created before");
			mResources.push_back(new T());
			mResources.back()->setName(id);
			return *dynamic_cast<T*>(mResources.back());
        }

		bool hasResource(const std::string& id) const;

		bool isResourceLoaded(const std::string& id) const;

		void releaseResource(const std::string& id);

		void releaseAllResources();

		bool loadResources(const std::string& filename);

    protected:
        std::vector<Resource*> mResources;
};

class Texture : public sf::Texture, public Resource
{
    public:
		Texture();
		Texture(std::string const& filename);

		bool loadFromFile(std::string const& filename, sf::IntRect const& area = sf::IntRect());
		bool loadFromMemory(void const* data, std::size_t size, sf::IntRect const& area = sf::IntRect());
		bool loadFromStream(sf::InputStream& stream, sf::IntRect const& area = sf::IntRect());
		bool loadFromImage(sf::Image const& image, sf::IntRect const& area = sf::IntRect());
};

class Image : public sf::Image, public Resource
{
    public:
		Image();
		Image(std::string const& filename);

		bool loadFromFile(std::string const& filename);
		bool loadFromMemory(void const* data, std::size_t size);
		bool loadFromStream(sf::InputStream& stream);
};

class Font : public sf::Font, public Resource
{
    public:
		Font();
		Font(std::string const& filename);

		bool loadFromFile(std::string const& filename);
		bool loadFromMemory(void const* data, std::size_t size);
		bool loadFromStream(sf::InputStream& stream);
};

class SoundBuffer : public sf::SoundBuffer, public Resource
{
    public:
		SoundBuffer();
		SoundBuffer(std::string const& filename);

		bool loadFromFile(std::string const& filename);
		bool loadFromMemory(void const* data, std::size_t size);
		bool loadFromStream(sf::InputStream& stream);
		bool loadFromSamples(sf::Int16 const* samples, sf::Uint64 sampleCount, unsigned int channelCount, unsigned int sampleRate);
};

class Shader : public sf::Shader, public Resource
{
    public:
		Shader();
		Shader(std::string const& filename, sf::Shader::Type type);
		Shader(std::string const& vertexShaderFilename, std::string const& fragmentShaderFilename);

		bool loadFromFile(std::string const& filename, sf::Shader::Type type);
		bool loadFromFile(std::string const& vertexShaderFilename, std::string const& fragmentShaderFilename);
		bool loadFromMemory(std::string const& shader, sf::Shader::Type type);
		bool loadFromMemory(std::string const& vertexShader, std::string const& fragmentShader);
		bool loadFromStream(sf::InputStream& stream, sf::Shader::Type type);
		bool loadFromStream(sf::InputStream& vertexShaderStream, sf::InputStream& fragmentShaderStream);

		void setUniform(std::string const& name, float x);
		float getUniformFloat(std::string const& name);

		void setUniform(std::string const& name, sf::Vector2f const& vector);
		sf::Vector2f getUniformVector2f(std::string const& name);

		void setUniform(std::string const& name, sf::Vector3f const& vector);
		sf::Vector3f getUniformVector3f(std::string const& name);

		void setUniform(std::string const& name, sf::Color const& color);
		sf::Color getUniformColor(std::string const& name);

		void setUniform(std::string const& name, sf::Texture const& texture);

    protected:
        std::map<std::string, float> mFloats;
		std::map<std::string, sf::Vector2f> mVectors2f;
		std::map<std::string, sf::Vector3f> mVectors3f;
		std::map<std::string, sf::Color> mColors;
};

class Theme : public Resource
{
	public:
		Theme();

		Theme(std::string const& filename);

		bool loadFromFile(std::string const& filename);

		tgui::WidgetConverter create(std::string const& className);

	private:
		tgui::Theme::Ptr mTheme;
};

class Tileset : public Resource, public PropertiesHolder
{
	public:
		Tileset();
		Tileset(pugi::xml_node const& node, std::string const& mapPath);

		bool loadFromNode(pugi::xml_node const& node, std::string const& mapPath);
		bool saveToNode(pugi::xml_node& node);

		unsigned int getFirstGid() const;
		const sf::Vector2i& getTileSize() const;
		unsigned int getSpacing() const;
		unsigned int getMargin() const;
		unsigned int getTileCount() const;
		unsigned int getColumns() const;
		const sf::Vector2f& getTileOffset() const;
		const std::string& getImageSource() const;
		sf::Color getImageTransparent() const;
		const sf::Vector2i& getImageSize() const;
		void setFirstGid(unsigned int id);
		void setTileSize(sf::Vector2i const& tileSize);
		void setSpacing(unsigned int spacing);
		void setMargin(unsigned int margin);
		void setTileCount(unsigned int tileCount);
		void setColumns(unsigned int columns);

		sf::Texture& getTexture();
		bool possess(unsigned int gid);
		sf::Vector2i toPos(unsigned int gid);
		sf::IntRect toRect(unsigned int gid);
		unsigned int toId(sf::Vector2i const& pos);

	private:
		std::string mMapPath;

		unsigned int mFirstGid;
		sf::Vector2i mTileSize;
		unsigned int mSpacing;
		unsigned int mMargin;
		unsigned int mTileCount;
		unsigned int mColumns;

		sf::Texture mTexture;
		std::string mImageSource;
		sf::Color mImageTransparent;

		bool mImageChanged;
};

class Lang : public Resource
{
	public:
		Lang();

		void add(const std::string& id, const std::string& value);

		std::string operator() (std::string const& id) const
		{
			if (mLang.find(id) != mLang.end())
			{
				return mLang.at(id);
			}
			return "";
		}

	protected:
		std::unordered_map<std::string, std::string> mLang;
};

class IniParser : public Resource
{
	public:
		IniParser() {}
		IniParser(std::string const& filename);

		Variant& operator[](const std::string& id)
		{
			for (std::size_t i = 0; i < mPairs.size(); i++)
			{
				if (mPairs[i].first == id)
				{
					return mPairs[i].second;
				}
			}
			mPairs.push_back(std::pair<std::string, Variant>(id, std::string()));
			return mPairs.back().second;
		}

		bool loadFromFile(std::string const& filename);
		bool saveToFile(std::string const& filename) const;

	private:
		std::vector<std::pair<std::string, Variant>> mPairs;
};

class Animation : public Resource
{
	public:
		struct Frame
		{
			std::string textureName;
			sf::IntRect textureRect;
			sf::Time duration;
		};

	public:
		Animation();

		void addFrame(Animation::Frame const& frame = Animation::Frame());
		void addFrame(std::string const& textureName, sf::IntRect const& textureRect, sf::Time duration);

		std::size_t getFrameCount() const;

		Animation::Frame& getFrame(std::size_t index);

		void removeFrame(std::size_t index);

		void removeAllFrames();

		sf::Time getDuration() const;

	private:
		std::vector<Animation::Frame> mFrames;
};

} // namespace ke

#endif // KE_RESOURCEMANAGER_HPP
