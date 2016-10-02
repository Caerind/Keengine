#ifndef KE_DIRECTIONLIGHTCOMPONENT_HPP
#define KE_DIRECTIONLIGHTCOMPONENT_HPP

#include "../Core/SceneComponent.hpp"
#include "../ExtLibs/LetThereBeLight.hpp"

namespace ke
{

class DirectionLightComponent : public Component
{
	public:
		typedef std::shared_ptr<DirectionLightComponent> Ptr;

		TYPE(DirectionLightComponent)

		DirectionLightComponent(Actor& actor);

		void onRegister();
		void onUnregister();

		void setColor(sf::Color color);
		sf::Color getColor() const;

		void setAngle(float angle);
		float getAngle() const;
		void setDirection(sf::Vector2f const& vector);
		sf::Vector2f getDirection() const;

		virtual void serialize(Serializer& serializer);
		virtual bool deserialize(Serializer& serializer, const std::string& identifier);

	protected:
		ltbl::LightDirectionEmission* mLight;
};

} // namespace ke

#endif // KE_DIRECTIONLIGHTCOMPONENT_HPP
