#ifndef KE_SHAPECOMPONENT_HPP
#define KE_SHAPECOMPONENT_HPP

#include "../Core/SceneComponent.hpp"

#include "../ExtLibs/LTBL2/LightShape.hpp"

namespace ke
{

class ShapeComponent : public SceneComponent
{
	public:
		typedef std::shared_ptr<ShapeComponent> Ptr;

		ShapeComponent(Actor& actor);

		void onRegister();
		void onUnregister();

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

		sf::FloatRect getLocalBounds();
		sf::FloatRect getGlobalBounds();

	private:
		virtual void renderCurrent(sf::RenderTarget& target, sf::RenderStates states);

	private:
		sf::ConvexShape mShape;
		ltbl::LightShape::Ptr mLightShape;
};

} // namespace ke

#endif // KE_SHAPECOMPONENT_HPP
