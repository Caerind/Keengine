#ifndef MAP_HPP
#define MAP_HPP

#include "Actor.hpp"

#include "../Components/LayerComponent.hpp"

class Map : public Actor, public PropertiesHolder
{
	public:
		typedef std::shared_ptr<Map> Ptr;

		Map();

		bool loadTmxFile(std::string const& filename);
		bool saveTmxFile(std::string const& filename);

		// TODO : Conversion of coordinates

		Tileset* getTileset();
		void setTileset(Tileset* tileset);

		LayerComponent* addLayer();
		LayerComponent* createLayer(std::string const& tilesetName = "", sf::Vector2i const& size = sf::Vector2i(), sf::Vector2i const& tileSize = sf::Vector2i(), std::string const& orientation = "orthogonal", std::string const& staggerAxis = "y", std::string const& staggerIndex = "odd", unsigned int hexSideLength = 0);
		std::size_t getLayerCount();
		LayerComponent* getLayer(std::size_t index);
		LayerComponent* getLayer(std::string const& name);
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

	private:
		std::vector<LayerComponent> mLayers;
		Tileset* mTileset;

		sf::Vector2i mSize;
		sf::Vector2i mTileSize;
		std::string mOrientation;
		std::string mStaggerAxis;
		std::string mStaggerIndex;
		unsigned int mHexSideLength;
};

#endif // MAP_HPP