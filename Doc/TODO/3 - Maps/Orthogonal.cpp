#include "Orthogonal.hpp"

#include "../Utils/Container.hpp"
#include "../Utils/Math.hpp"

namespace NOrthogonal
{

sf::Vector2i gTileSize = sf::Vector2i(1,1);
sf::Vector2i gLayerSize = sf::Vector2i(1,1);

sf::Vector2i worldToCoords(sf::Vector2f const& pos)
{
    return {(int)pos.x / getTileSize().x, (int)pos.y / getTileSize().y};
}

sf::Vector2i worldToChunk(sf::Vector2f const& pos)
{
    return coordsToChunk(worldToCoords(pos));
}

sf::Vector2i worldToRelative(sf::Vector2f const& pos)
{
    return coordsToRelative(worldToCoords(pos));
}

sf::Vector2f coordsToWorld(sf::Vector2i const& coords)
{
    return {coords.x * getTileSize().x + 0.5f * getTileSize().x, coords.y * getTileSize().y + 0.5f * getTileSize().y};
}

sf::Vector2i coordsToChunk(sf::Vector2i const& coords)
{
    sf::Vector2i c;
    if (getLayerSize() != sf::Vector2i(0,0))
    {
        c.x = coords.x / getLayerSize().x;
        c.y = coords.y / getLayerSize().y;
        if (coords.x < 0)
        {
            c.x--;
        }
        if (coords.y < 0)
        {
            c.y--;
        }
    }
    return c;
}

sf::Vector2i coordsToRelative(sf::Vector2i const& coords)
{
    sf::Vector2i c;
    c.x  = coords.x % getLayerSize().x;
    c.y  = coords.y % getLayerSize().y;
    if (c.x < 0)
    {
        c.x += getLayerSize().x;
    }
    if (c.y < 0)
    {
        c.y += getLayerSize().y;
    }
    return c;
}

std::vector<sf::Vector2i> getNeighboors(sf::Vector2i const& coords, bool diag)
{
    std::vector<sf::Vector2i> n;
	n.push_back({coords.x, coords.y - 1});
	n.push_back({coords.x, coords.y + 1});
	n.push_back({coords.x - 1, coords.y});
	n.push_back({coords.x + 1, coords.y});
	if (diag)
    {
        n.push_back({coords.x + 1, coords.y - 1});
        n.push_back({coords.x + 1, coords.y + 1});
        n.push_back({coords.x - 1, coords.y + 1});
        n.push_back({coords.x - 1, coords.y - 1});
    }
    return n;
}

namespace priv
{
    struct Node
    {
        Node(sf::Vector2i c, sf::Vector2i p) { coords = c; parent = p; }
        sf::Vector2i coords;
        sf::Vector2i parent;
    };
} // namespace priv

std::vector<sf::Vector2i> pathfinding(sf::Vector2i const& begin, sf::Vector2i const& end)
{
    std::vector<priv::Node> container;
    add(container, priv::Node(begin,begin));
    std::size_t test = 0;
    bool reached = false;
    while (test < 50 && !reached)
    {
        std::vector<priv::Node> temp;
        for (std::size_t i = 0; i < container.size(); i++)
        {
            std::vector<sf::Vector2i> n = getNeighboors(container[i].coords);
            for (std::size_t j = 0; j < n.size(); j++)
            {
                bool found = false;
                for (std::size_t k = 0; k < container.size(); k++)
                {
                    if (container[k].coords == n[j])
                    {
                        found = true;
                    }
                }
                for (std::size_t k = 0; k < temp.size(); k++)
                {
                    if (temp[k].coords == n[j])
                    {
                        found = true;
                    }
                }
                if (!found)
                {
                    add(temp, priv::Node(n[j], container[i].coords));
                    if (n[j] == end)
                    {
                        reached = true;
                    }
                }
            }
        }
        append(container, temp);
        test++;
    }

    std::vector<sf::Vector2i> path;
    if (reached)
    {
        sf::Vector2i pos = end;
        reached = false;
        while (!reached)
        {
            bool handled = false;
            for (std::size_t i = 0; i < container.size(); i++)
            {
                if (container[i].coords == pos && !handled)
                {
                    add(path, pos);
                    if (container[i].parent == container[i].coords)
                    {
                        reached = true;
                    }
                    pos = container[i].parent;
                    handled = true;
                }
            }
        }
        std::reverse(path.begin(),path.end());
    }
    return path;
}

void setTileSize(sf::Vector2i const& tileSize)
{
    gTileSize = tileSize;
}

void setLayerSize(sf::Vector2i const& layerSize)
{
    gLayerSize = layerSize;
}

sf::Vector2i getTileSize()
{
    return gTileSize;
}

sf::Vector2i getLayerSize()
{
    return gLayerSize;
}

} // namespace NOrthogonal
