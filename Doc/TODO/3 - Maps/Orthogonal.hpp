#ifndef NORTHOGONAL_HPP
#define NORTHOGONAL_HPP

#include "LayerComponent.hpp"
#include "Map.hpp"
#include "World.hpp"

namespace NOrthogonal
{

// This is just to have the same interface for all type
class NLayerComponent : public ::NLayerComponent
{
    public:
        NLayerComponent(sf::Vector2i coords = sf::Vector2i(0,0)) { mCoords = coords; }
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

class NMap : public ::NMap<NOrthogonal::NLayerComponent>
{
    public:
        NMap()
        {
            mTileSize = getTileSize();
            mLayerSize = getLayerSize();
        }

        void setTileId(sf::Vector2i const& chunk, sf::Vector2i const& tile, int id)
        {
            ::NMap<NOrthogonal::NLayerComponent>::setTileId(chunk,tile,id);
        }

        int getTileId(sf::Vector2i const& chunk, sf::Vector2i const& tile) const
        {
            return ::NMap<NOrthogonal::NLayerComponent>::getTileId(chunk,tile);
        }

        void setTileId(sf::Vector2i const& coords, int id)
        {
            sf::Vector2i chunkCoords = NOrthogonal::coordsToChunk(coords);
            sf::Vector2i tileCoords = NOrthogonal::coordsToRelative(coords);
            setTileId(chunkCoords, tileCoords, id);
        }

        int getTileId(sf::Vector2i const& coords) const
        {
            sf::Vector2i chunkCoords = NOrthogonal::coordsToChunk(coords);
            sf::Vector2i tileCoords = NOrthogonal::coordsToRelative(coords);
            return getTileId(chunkCoords, tileCoords);
        }
};

} // namespace NOrthogonal

#endif // NORTHOGONAL_HPP
