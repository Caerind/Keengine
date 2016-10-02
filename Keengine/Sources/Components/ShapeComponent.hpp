#ifndef KE_SHAPECOMPONENT_HPP
#define KE_SHAPECOMPONENT_HPP

#include <SFML/Graphics/ConvexShape.hpp>

#include "../ExtLibs/Box2D/Box2D.h"
#include "../ExtLibs/LetThereBeLight.hpp"

#include "../Core/SceneComponent.hpp"

namespace ke
{

class ShapeComponent : public SceneComponent
{
	public:
		typedef std::shared_ptr<ShapeComponent> Ptr;

		TYPE(ShapeComponent)

		enum Options
		{
			None = 0,
			Graphic = 1 << 0,
			Physic = 1 << 1,
			Trigger = 1 << 2,
			Light = 1 << 3,
		};

		ShapeComponent(Actor& actor, sf::Uint32 options = Options::Graphic | Options::Physic | Options::Light);

		void onRegister();
		void onUnregister();

		bool useGraphic();
		bool usePhysic();
		bool useLight();

		void setPointCount(std::size_t points);
		std::size_t getPointCount() const;

		void setPoint(std::size_t index, sf::Vector2f const& point);
		sf::Vector2f getPoint(std::size_t index) const;

		void setOutlineThickness(float thickness);
		float getOutlineThickness() const;

		void setOutlineColor(sf::Color const& color);
		sf::Color getOutlineColor() const;

		void setFillColor(sf::Color const& color);
		sf::Color getFillColor() const;

		sf::FloatRect getLocalBounds();
		sf::FloatRect getGlobalBounds();

		b2Fixture* getFixture();
		b2Shape* getShape();
		b2PolygonShape* getPolygonShape();

		void setDensity(float density);
		float getDensity() const;

		void setPoints(const std::vector<sf::Vector2f>& points);
		std::vector<sf::Vector2f> getPoints() const;

		virtual void serialize(Serializer& serializer);
		virtual bool deserialize(Serializer& serializer, const std::string& identifier);

	private:
		virtual void renderCurrent(sf::RenderTarget& target, sf::RenderStates states);
		virtual void onTransformUpdated();
		void updatePhysicShape();

	private:
		sf::Uint32 mOptions;
		std::vector<sf::Vector2f> mPoints;
		sf::ConvexShape mShape;
		b2Fixture* mFixture;
		ltbl::LightShape* mLightShape;
};

} // namespace ke

#endif // KE_SHAPECOMPONENT_HPP
