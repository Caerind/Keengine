#ifndef KE_MAP_HPP
#define KE_MAP_HPP

#include "Actor.hpp"

#include "../Components/LayerComponent.hpp"
#include "../Components/SpriteComponent.hpp"

namespace ke
{

class Map : public Actor, public PropertiesHolder
{
	public:
		typedef std::shared_ptr<Map> Ptr;

		static std::vector<sf::Vector2i> getNeighboors(sf::Vector2i const& coords, std::string const& orientation, bool diag = false, std::string const& staggerIndex = "odd", std::string const& staggerAxis = "y");
		static sf::Vector2i worldToCoords(sf::Vector2f const& world, std::string const& orientation, sf::Vector2i const& tileSize, std::string const& staggerIndex = "odd", std::string const& staggerAxis = "y", unsigned int hexSide = 0);
		static sf::Vector2f coordsToWorld(sf::Vector2i const& coords, std::string const& orientation, sf::Vector2i const& tileSize, std::string const& staggerIndex = "odd", std::string const& staggerAxis = "y", unsigned int hexSide = 0);

		Map(Scene& scene);

		bool loadTmxFile(std::string const& filename);
		bool saveTmxFile(std::string const& filename);

		sf::Vector2i worldToCoords(sf::Vector2f const& world);
		sf::Vector2f coordsToWorld(sf::Vector2i const& coords);

		std::size_t getImageCount();
		std::shared_ptr<SpriteComponent> getImage(std::size_t index);
		void removeImage(std::size_t index);
		void clearImages();

		Tileset* getTileset();
		void setTileset(Tileset* tileset);

		std::shared_ptr<LayerComponent> createLayer(std::string const& tilesetName = "", sf::Vector2i const& size = sf::Vector2i(), sf::Vector2i const& tileSize = sf::Vector2i(), std::string const& orientation = "orthogonal", std::string const& staggerAxis = "y", std::string const& staggerIndex = "odd", unsigned int hexSideLength = 0);
		std::size_t getLayerCount();
		std::shared_ptr<LayerComponent> getLayer(std::size_t index);
		std::shared_ptr<LayerComponent> getLayer(std::string const& name);
		bool hasLayer(std::string const& name);
		void removeLayer(std::size_t index);
		void removeLayer(std::string const& name);
		void clearLayers();

		const sf::Vector2i& getSize() const;
		void setSize(sf::Vector2i const& size);

		const sf::Vector2i& getTileSize() const;
		void setTileSize(sf::Vector2i const& tileSize);

		const std::string& getOrientation() const;
		void setOrientation(std::string const& orientation);

		const std::string& getStaggerAxis() const;
		void setStaggerAxis(std::string const& axis);

		const std::string& getStaggerIndex() const;
		void setStaggerIndex(std::string const& index);

		unsigned int getHexSizeLength() const;
		void setHexSideLength(unsigned int hexSideLength);

	protected:
		std::vector<std::shared_ptr<SpriteComponent>> mImages;
		std::vector<std::shared_ptr<LayerComponent>> mLayers;
		Tileset* mTileset;

		sf::Vector2i mSize;
		sf::Vector2i mTileSize;
		std::string mOrientation;
		std::string mStaggerAxis;
		std::string mStaggerIndex;
		unsigned int mHexSideLength;
};

} // namespace ke

#endif // KE_MAP_HPP