#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include <cassert>
#include <iostream>
#include <map>
#include <string>

#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "../System/Log.hpp"
#include "../ExtLibs/TGUI/Loading/Theme.hpp"

class Resource
{
    public:
		Resource();
		virtual ~Resource();

		bool isLoaded() const;

    protected:
        bool mLoaded;
};

class ResourceManager
{
    public:
		ResourceManager();

		~ResourceManager();

        template <typename T, typename ... Args>
        T& createResource(std::string const& id, Args&& ... args)
        {
            mResources[id] = new T(std::forward<Args>(args)...);
            return *dynamic_cast<T*>(mResources[id]);
        }

        template <typename T>
        T& getResource(std::string const& id)
        {
            auto itr = mResources.find(id);
            if (itr == mResources.end())
            {
                Log::instance() << Log::Error << std::string("Resource with id (" + id + ") don't exist");
            }
            return *dynamic_cast<T*>(mResources[id]);
        }

		bool hasResource(std::string const& id) const;

		bool isResourceLoaded(std::string const& id) const;

		void releaseResource(std::string const& id);

		void releaseAllResources();

    protected:
        std::map<std::string,Resource*> mResources;
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

// Improvements
// - Add uniform types
class Shader : public sf::Shader, public Resource
{
    public:
		Shader();

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

#endif // RESOURCEMANAGER_HPP
