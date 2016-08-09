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

class Resource
{
    public:
        Resource() { mLoaded = false; }
        virtual ~Resource() {}

        bool isLoaded() const { return mLoaded; }

    protected:
        bool mLoaded;
};

class ResourceManager
{
    public:
        ResourceManager()
        {
        }

        ~ResourceManager()
        {
            releaseAllResources();
        }

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

        bool hasResource(std::string const& id) const
        {
            auto itr = mResources.find(id);
            return (itr != mResources.end() && itr->second != nullptr);
        }

        bool isResourceLoaded(std::string const& id) const
        {
            return (hasResource(id) && mResources.find(id)->second->isLoaded());
        }

        void releaseResource(std::string const& id)
        {
            if (mResources.find(id) != mResources.end())
            {
                delete mResources[id];
                mResources.erase(mResources.find(id));
            }
        }

        void releaseAllResources()
        {
            for (auto itr = mResources.begin(); itr != mResources.end(); itr++)
            {
                delete itr->second;
            }
            mResources.clear();
        }

    protected:
        std::map<std::string,Resource*> mResources;
};

class Texture : public sf::Texture, public Resource
{
    public:
        Texture() {}
		Texture(std::string const& filename) { loadFromFile(filename); }

        bool loadFromFile(std::string const& filename, sf::IntRect const& area = sf::IntRect()) { bool r = sf::Texture::loadFromFile(filename, area); mLoaded = r; return r; }
        bool loadFromMemory(void const* data, std::size_t size, sf::IntRect const& area = sf::IntRect()) { bool r = sf::Texture::loadFromMemory(data, size, area); mLoaded = r; return r; }
        bool loadFromStream(sf::InputStream& stream, sf::IntRect const& area = sf::IntRect()) { bool r = sf::Texture::loadFromStream(stream, area); mLoaded = r; return r; }
        bool loadFromImage(sf::Image const& image, sf::IntRect const& area = sf::IntRect()) { bool r = sf::Texture::loadFromImage(image, area); mLoaded = r; return r; }
};

class Image : public sf::Image, public Resource
{
    public:
        Image() {}
		Image(std::string const& filename) { loadFromFile(filename); }

        bool loadFromFile(std::string const& filename) { bool r = sf::Image::loadFromFile(filename); mLoaded = r; return r; }
        bool loadFromMemory(void const* data, std::size_t size) { bool r = sf::Image::loadFromMemory(data, size); mLoaded = r; return r; }
        bool loadFromStream(sf::InputStream& stream) { bool r = sf::Image::loadFromStream(stream); mLoaded = r; return r; }
};

class Font : public sf::Font, public Resource
{
    public:
        Font() {}
		Font(std::string const& filename) { loadFromFile(filename); }

        bool loadFromFile(std::string const& filename) { bool r = sf::Font::loadFromFile(filename); mLoaded = r; return r; }
        bool loadFromMemory(void const* data, std::size_t size) { bool r = sf::Font::loadFromMemory(data, size); mLoaded = r; return r; }
        bool loadFromStream(sf::InputStream& stream) { bool r = sf::Font::loadFromStream(stream); mLoaded = r; return r; }
};

class SoundBuffer : public sf::SoundBuffer, public Resource
{
    public:
        SoundBuffer() {}
		SoundBuffer(std::string const& filename) { loadFromFile(filename); }

        bool loadFromFile(std::string const& filename) { bool r = sf::SoundBuffer::loadFromFile(filename); mLoaded = r; return r; }
        bool loadFromMemory(void const* data, std::size_t size) { bool r = sf::SoundBuffer::loadFromMemory(data, size); mLoaded = r; return r; }
        bool loadFromStream(sf::InputStream& stream) { bool r = sf::SoundBuffer::loadFromStream(stream); mLoaded = r; return r; }
        bool loadFromSamples(sf::Int16 const* samples, sf::Uint64 sampleCount, unsigned int channelCount, unsigned int sampleRate) { bool r = sf::SoundBuffer::loadFromSamples(samples, sampleCount, channelCount, sampleRate); mLoaded = r; return r; }
};

// Improvements
// - Add uniform types
class Shader : public sf::Shader, public Resource
{
    public:
        Shader() {}

        bool loadFromFile(std::string const& filename, sf::Shader::Type type) { bool r = sf::Shader::loadFromFile(filename, type); mLoaded = r; return r; }
        bool loadFromFile(std::string const& vertexShaderFilename, std::string const& fragmentShaderFilename) { bool r = sf::Shader::loadFromFile(vertexShaderFilename, fragmentShaderFilename); mLoaded = r; return r; }
        bool loadFromMemory(std::string const& shader, sf::Shader::Type type) { bool r = sf::Shader::loadFromMemory(shader, type); mLoaded = r; return r; }
        bool loadFromMemory(std::string const& vertexShader, std::string const& fragmentShader) { bool r = sf::Shader::loadFromMemory(vertexShader, fragmentShader); mLoaded = r; return r; }
        bool loadFromStream(sf::InputStream& stream, sf::Shader::Type type) { bool r = sf::Shader::loadFromStream(stream, type); mLoaded = r; return r; }
        bool loadFromStream(sf::InputStream& vertexShaderStream, sf::InputStream& fragmentShaderStream) { bool r = sf::Shader::loadFromStream(vertexShaderStream, fragmentShaderStream); mLoaded = r; return r; }

        void setUniform(std::string const& name, float x)
        {
            sf::Shader::setParameter(name,x);
            mFloats[name] = x;
        }

        float getUniformFloat(std::string const& name)
        {
            return mFloats[name];
        }

    protected:
        std::map<std::string,float> mFloats;
};

#endif // RESOURCEMANAGER_HPP
