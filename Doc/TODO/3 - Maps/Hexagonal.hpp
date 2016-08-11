#ifndef NHEXAGONAL_HPP
#define NHEXAGONAL_HPP

#include "LayerComponent.hpp"
#include "Map.hpp"
#include "World.hpp"

namespace NHexagonal
{

class NLayerComponent : public ::NLayerComponent
{
    public:
        NLayerComponent(sf::Vector2i coords = sf::Vector2i(0,0));
        NLayerComponent(std::string const& textureName, sf::Vector2i layerSize, sf::Vector2i tileSize, int hexSide, sf::Vector2i coords = sf::Vector2i(0,0));

        void create(std::string const& textureName, sf::Vector2i layerSize, sf::Vector2i tileSize, int hexSide);

        sf::FloatRect getBounds() const;

        virtual void load(pugi::xml_node& node, std::string const& name = "LayerComponent");
        virtual void save(pugi::xml_node& node, std::string const& name = "LayerComponent");

    protected:
        int mHexSide;
};

sf::Vector2i worldToCoords(sf::Vector2f const& pos);
sf::Vector2i worldToChunk(sf::Vector2f const& pos);
sf::Vector2i worldToRelative(sf::Vector2f const& pos);

sf::Vector2f coordsToWorld(sf::Vector2i const& coords); // center of the tile
sf::Vector2i coordsToChunk(sf::Vector2i const& coords);
sf::Vector2i coordsToRelative(sf::Vector2i const& coords);

std::vector<sf::Vector2i> getNeighboors(sf::Vector2i const& coords, bool diag = false);
std::vector<sf::Vector2i> pathfinding(sf::Vector2i const& begin, sf::Vector2i const& end);

void setTileSize(sf::Vector2i const& tileSize);
void setLayerSize(sf::Vector2i const& layerSize);
sf::Vector2i getTileSize();
sf::Vector2i getLayerSize();

class NMap : public ::NMap<NHexagonal::NLayerComponent>
{
    public:
        NMap()
        {
            mTileSize = getTileSize();
            mLayerSize = getLayerSize();
        }

        void setTileId(sf::Vector2i const& chunk, sf::Vector2i const& tile, int id)
        {
            ::NMap<NHexagonal::NLayerComponent>::setTileId(chunk,tile,id);
        }

        int getTileId(sf::Vector2i const& chunk, sf::Vector2i const& tile) const
        {
            return ::NMap<NHexagonal::NLayerComponent>::getTileId(chunk,tile);
        }

        void setTileId(sf::Vector2i const& coords, int id)
        {
            sf::Vector2i chunkCoords = NHexagonal::coordsToChunk(coords);
            sf::Vector2i tileCoords = NHexagonal::coordsToRelative(coords);
            setTileId(chunkCoords, tileCoords, id);
        }

        int getTileId(sf::Vector2i const& coords) const
        {
            sf::Vector2i chunkCoords = NHexagonal::coordsToChunk(coords);
            sf::Vector2i tileCoords = NHexagonal::coordsToRelative(coords);
            return getTileId(chunkCoords, tileCoords);
        }
};

} // namespace NHexagonal

#endif // NHEXAGONAL_HPP
