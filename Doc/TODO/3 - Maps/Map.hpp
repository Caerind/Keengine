#ifndef NMAP_HPP
#define NMAP_HPP

#include "Actor.hpp"
#include "LayerComponent.hpp"

template <typename T>
class NMap : public NActor
{
    public:
        typedef std::shared_ptr<NMap<T>> Ptr;

    public:
        NMap();
        ~NMap();

        void addChunk(std::string const& textureName, sf::Vector2i const& coords);
        void removeChunk(sf::Vector2i const& coords);

        std::size_t getChunkCount() const;

        void setTileId(sf::Vector2i const& chunk, sf::Vector2i const& tile, int id);
        int getTileId(sf::Vector2i const& chunk, sf::Vector2i const& tile) const;

        void setTileId(sf::Vector2i const& coords, int id);
        int getTileId(sf::Vector2i const& coords) const;

        void load(pugi::xml_node& node);
        void save(pugi::xml_node& node);

    protected:
        bool contains(sf::Vector2i const& coords) const;

    protected:
        std::vector<T*> mChunks;
        sf::Vector2i mTileSize;
        sf::Vector2i mLayerSize;
};

template <typename T>
NMap<T>::NMap()
{
}

template <typename T>
NMap<T>::~NMap()
{
    for (std::size_t i = 0; i < mChunks.size(); i++)
    {
        removeChunk(mChunks[i]->getCoords());
    }
    mChunks.clear();
}

template <typename T>
void NMap<T>::addChunk(std::string const& textureName, sf::Vector2i const& coords)
{
    if (!contains(coords))
    {
        mChunks.push_back(new T(textureName,coords));
        attachComponent(mChunks.back());
    }
}

template <typename T>
void NMap<T>::removeChunk(sf::Vector2i const& coords)
{
    for (std::size_t i = 0; i < mChunks.size();)
    {
        if (mChunks[i]->getCoords() == coords)
        {
            detachComponent(mChunks[i]);
            delete mChunks[i];
            mChunks.erase(mChunks.begin() + i);
        }
        else
        {
            i++;
        }
    }
}

template <typename T>
std::size_t NMap<T>::getChunkCount() const
{
    return mChunks.size();
}

template <typename T>
void NMap<T>::setTileId(sf::Vector2i const& chunk, sf::Vector2i const& tile, int id)
{
    for (std::size_t i = 0; i < mChunks.size(); i++)
    {
        if (mChunks[i]->getCoords() == chunk)
        {
            mChunks[i]->setTileId(tile, id);
        }
    }
}

template <typename T>
int NMap<T>::getTileId(sf::Vector2i const& chunk, sf::Vector2i const& tile) const
{
    for (std::size_t i = 0; i < mChunks.size(); i++)
    {
        if (mChunks[i]->getCoords() == chunk)
        {
            return mChunks[i]->getTileId(tile);
        }
    }
    return 0;
}

template <typename T>
void NMap<T>::load(pugi::xml_node& node)
{
}

template <typename T>
void NMap<T>::save(pugi::xml_node& node)
{
    node.append_attribute("type") = "Map";
}

template <typename T>
bool NMap<T>::contains(sf::Vector2i const& coords) const
{
    for (std::size_t i = 0; i < mChunks.size(); i++)
    {
        if (mChunks[i]->getCoords() == coords)
        {
            return true;
        }
    }
    return false;
}

#endif // NMAP_HPP
