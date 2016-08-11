#ifndef NLAYERCOMPONENT_HPP
#define NLAYERCOMPONENT_HPP

#include <vector>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include "SceneComponent.hpp"

class NLayerComponent : public NSceneComponent
{
    public:
        NLayerComponent(sf::Vector2i coords = sf::Vector2i(0,0));
        NLayerComponent(std::string const& textureName, sf::Vector2i layerSize, sf::Vector2i tileSize, sf::Vector2i coords = sf::Vector2i(0,0));

        void create(std::string const& textureName, sf::Vector2i layerSize, sf::Vector2i tileSize);

        sf::Vector2i getCoords() const;

        bool loadFromCode(std::string const& code);
        std::string getCode() const;

        sf::Vector2i getLayerSize() const;
        sf::Vector2i getTileSize() const;

        void render(sf::RenderTarget& target);

        sf::FloatRect getBounds() const;

        void fill(int id);

        void setTileId(sf::Vector2i const& coords, int id);
        int getTileId(sf::Vector2i const& coords) const;

        sf::IntRect idToRect(int id) const;
        int rectToId(sf::IntRect const& rect) const;

        virtual void load(pugi::xml_node& node, std::string const& name = "LayerComponent");
        virtual void save(pugi::xml_node& node, std::string const& name = "LayerComponent");

    protected:
        sf::Vector2i mCoords;
        sf::VertexArray mVertices;
        sf::Texture* mTexture;
        std::string mTextureName;
        sf::Vector2i mLayerSize;
        sf::Vector2i mTileSize;
};

#endif // NLAYERCOMPONENT_HPP
