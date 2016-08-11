#include "Isometric.hpp"

#include "../Utils/Container.hpp"
#include "../Utils/Math.hpp"
#include "World.hpp"

namespace NIsometric
{

sf::Vector2i gTileSize = sf::Vector2i(1,1);
sf::Vector2i gLayerSize = sf::Vector2i(1,1);

NLayerComponent::NLayerComponent(sf::Vector2i coords)
{
    mCoords = coords;
}

NLayerComponent::NLayerComponent(std::string const& textureName, sf::Vector2i coords)
{
    mCoords = coords;
    setPosition(mCoords.x * NIsometric::getLayerSize().x * NIsometric::getTileSize().x, mCoords.y * 0.5f * NIsometric::getLayerSize().y * NIsometric::getTileSize().y);
    create(textureName,NIsometric::getLayerSize(),NIsometric::getTileSize());
}

NLayerComponent::NLayerComponent(std::string const& textureName, sf::Vector2i layerSize, sf::Vector2i tileSize, sf::Vector2i coords)
{
    mCoords = coords;
    setPosition(mCoords.x * layerSize.x * tileSize.x, mCoords.y * 0.5f * layerSize.y * tileSize.y);
    create(textureName,layerSize,tileSize);
}

void NLayerComponent::create(std::string const& textureName, sf::Vector2i layerSize, sf::Vector2i tileSize)
{
    mTextureName = textureName;
    mLayerSize = layerSize;
    mTileSize = tileSize;

    mTexture = nullptr;
    mTexture = &NWorld::getResources().getTexture(textureName);

    mVertices.setPrimitiveType(sf::Quads);
    mVertices.resize(mLayerSize.x * mLayerSize.y * 4);

    for (int i = 0; i < mLayerSize.x; ++i)
    {
        for (int j = 0; j < mLayerSize.y; ++j)
        {
            sf::Vertex* quad = &mVertices[(i + j * mLayerSize.x) * 4];
            if (j % 2 == 0)
            {
                quad[0].position = {i * mTileSize.x * 1.f, j * mTileSize.y * 0.5f};
                quad[1].position = {(i + 1) * mTileSize.x * 1.f, j * mTileSize.y * 0.5f};
                quad[2].position = {(i + 1) * mTileSize.x * 1.f, j * mTileSize.y * 0.5f + mTileSize.y};
                quad[3].position = {i * mTileSize.x * 1.f, j * mTileSize.y * 0.5f + mTileSize.y};
            }
            else
            {
                quad[0].position = {(i + 0.5f) * mTileSize.x, j * mTileSize.y * 0.5f};
                quad[1].position = {(i + 1.5f) * mTileSize.x, j * mTileSize.y * 0.5f};
                quad[2].position = {(i + 1.5f) * mTileSize.x, j * mTileSize.y * 0.5f + mTileSize.y};
                quad[3].position = {(i + 0.5f) * mTileSize.x, j * mTileSize.y * 0.5f + mTileSize.y};
            }
        }
    }
}

sf::FloatRect NLayerComponent::getBounds() const
{
    return getFinalTransform().transformRect(sf::FloatRect(0, 0, mTileSize.x * mLayerSize.x, mTileSize.y * mLayerSize.y * 0.5f));
}


sf::Vector2i worldToCoords(sf::Vector2f const& pos)
{
    sf::Vector2f s = {getTileSize().x * 0.5f, getTileSize().y * 0.5f};
    sf::Vector2f mc = {(float)floor(pos.x / s.x), (float)floor(pos.y / s.y)};
    sf::Vector2f p = pos;
    p -= {mc.x * s.x, mc.y * s.y};
    if (((int)mc.x + (int)mc.y) % 2 == 0)
    {
        if (NMath::atan2(s.y - p.y,p.x) > 30.f)
        {
            mc.x--;
            mc.y--;
        }
    }
    else
    {
        if (NMath::atan2(-p.y,p.x) > -30.f)
        {
            mc.y--;
        }
        else
        {
            mc.x--;
        }
    }
    return {(int)floor(mc.x * 0.5f),(int)mc.y};
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
    sf::Vector2f ret;
    ret.y = coords.y * getTileSize().y * 0.5f + getTileSize().y * 0.5f;
    if (coords.y % 2 == 0)
    {
        ret.x = coords.x * getTileSize().x + getTileSize().x * 0.5f;
    }
    else
    {
        ret.x = coords.x * getTileSize().x + getTileSize().x;
    }
    return ret;
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

sf::Vector2i relativeToCoords(sf::Vector2i const& chunk, sf::Vector2i const& relative)
{
    sf::Vector2i c;
    c.x = chunk.x * getLayerSize().x + relative.x;
    c.y = chunk.y * getLayerSize().y + relative.y;
    return c;
}

std::vector<sf::Vector2i> getNeighboors(sf::Vector2i const& coords, bool diag)
{
    std::vector<sf::Vector2i> n;
    if (coords.y % 2 == 0)
    {
        n.push_back({coords.x - 1, coords.y - 1});
        n.push_back({coords.x, coords.y - 1});
        n.push_back({coords.x, coords.y + 1});
        n.push_back({coords.x - 1, coords.y + 1});
    }
    else
    {
        n.push_back({coords.x, coords.y - 1});
        n.push_back({coords.x + 1, coords.y - 1});
        n.push_back({coords.x + 1, coords.y + 1});
        n.push_back({coords.x, coords.y + 1});
    }
    if (diag)
    {
        n.push_back({coords.x, coords.y - 1});
        n.push_back({coords.x + 1, coords.y});
        n.push_back({coords.x, coords.y + 1});
        n.push_back({coords.x - 1, coords.y});
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

std::vector<sf::Vector2i> reorganizedNeighboors(sf::Vector2i const& pos, sf::Vector2i const& end)
{
    std::vector<sf::Vector2i> n = getNeighboors(pos,false);
    std::vector<sf::Vector2i> p;
    sf::Vector2f delta = coordsToWorld(end) - coordsToWorld(pos);
    if (isZero(delta))
    {
        return n;
    }
    float angle = getPolarAngle(delta);
    if (0.f <= angle && angle < 30.f) // 2130
    {
        p.push_back(n.at(2));
        p.push_back(n.at(1));
        p.push_back(n.at(3));
        p.push_back(n.at(0));
    }
    else if (30.f <= angle && angle < 90.f) // 2310
    {
        p.push_back(n.at(2));
        p.push_back(n.at(3));
        p.push_back(n.at(1));
        p.push_back(n.at(0));
    }
    else if (90.f <= angle && angle < 150.f) // 3201
    {
        p.push_back(n.at(3));
        p.push_back(n.at(2));
        p.push_back(n.at(0));
        p.push_back(n.at(1));
    }
    else if (150.f <= angle && angle < 180.f) // 3021
    {
        p.push_back(n.at(3));
        p.push_back(n.at(0));
        p.push_back(n.at(2));
        p.push_back(n.at(1));
    }
    else if (180.f <= angle && angle < 210.f) // 0312
    {
        p.push_back(n.at(0));
        p.push_back(n.at(3));
        p.push_back(n.at(1));
        p.push_back(n.at(2));
    }
    else if (210.f <= angle && angle < 270.f) // 0132
    {
        p.push_back(n.at(0));
        p.push_back(n.at(1));
        p.push_back(n.at(3));
        p.push_back(n.at(2));
    }
    else if (270.f <= angle && angle < 330.f) // 1023
    {
        p.push_back(n.at(1));
        p.push_back(n.at(0));
        p.push_back(n.at(2));
        p.push_back(n.at(3));
    }
    else // 1203
    {
        p.push_back(n.at(1));
        p.push_back(n.at(2));
        p.push_back(n.at(0));
        p.push_back(n.at(3));
    }
    return p;
}

} // namespace priv

std::vector<sf::Vector2i> pathfinding(sf::Vector2i const& begin, sf::Vector2i const& end, std::function<bool(sf::Vector2i const& coords)> collisions)
{
    std::vector<priv::Node> container;
    if (begin == end)
    {
        return {};
    }
    add(container, priv::Node(begin,begin));
    std::size_t test = 0;
    bool reached = false;
    while (test < 20 && !reached)
    {
        std::vector<priv::Node> temp;
        for (std::size_t i = 0; i < container.size(); i++)
        {
            std::vector<sf::Vector2i> n = priv::reorganizedNeighboors(container[i].coords, end);
            for (std::size_t j = 0; j < n.size(); j++)
            {
                bool addToList = true;
                if (collisions)
                {
                    if (collisions(n[j]))
                    {
                        addToList = false;
                    }
                }
                for (std::size_t k = 0; k < container.size(); k++)
                {
                    if (container[k].coords == n[j])
                    {
                        addToList = false;
                    }
                }
                for (std::size_t k = 0; k < temp.size(); k++)
                {
                    if (temp[k].coords == n[j])
                    {
                        addToList = false;
                    }
                }
                if (addToList)
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
        path.pop_back();
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

} // namespace NIsometric
