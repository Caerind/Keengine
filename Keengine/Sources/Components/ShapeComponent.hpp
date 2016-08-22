#ifndef SHAPECOMPONENT_HPP
#define SHAPECOMPONENT_HPP

#include "../Core/PrimitiveComponent.hpp"

#include "../ExtLibs/LTBL2/LightShape.hpp"

class ShapeComponent : public PrimitiveComponent
{
	public:
		ShapeComponent();
		~ShapeComponent();

		void setPointCount(std::size_t points);
		std::size_t getPointCount() const;

		void setPoint(std::size_t index, sf::Vector2f const& point);
		sf::Vector2f getPoint(std::size_t index) const;

		void setOutlineThickness(float thickness);
		float getOutlineThicnkess() const;

		void setOutlineColor(sf::Color const& color);
		sf::Color getOutlineColor() const;

		void setFillColor(sf::Color const& color);
		sf::Color getFillColor() const;

		void render(sf::RenderTarget& target);
		sf::FloatRect getLocalBounds();
		sf::FloatRect getGlobalBounds();

	private:
		sf::ConvexShape mShape;
		ltbl::LightShape::Ptr mLightShape;
};

#endif // SHAPECOMPONENT_HPP
