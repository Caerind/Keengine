#ifndef KE_POINTLIGHTCOMPONENT_HPP
#define KE_POINTLIGHTCOMPONENT_HPP

#include "../Core/SceneComponent.hpp"
#include "../ExtLibs/LetThereBeLight.hpp"

namespace ke
{

class PointLightComponent : public SceneComponent
{
	public:
		typedef std::shared_ptr<PointLightComponent> Ptr;

		TYPE(PointLightComponent)

		PointLightComponent(Actor& actor);

		void onRegister();
		void onUnregister();

		void setColor(sf::Color color);
		sf::Color getColor() const;

		void setIntensity(float intensity);
		float getIntensity() const;

		void setOn(bool on);
		bool isOn() const;

		virtual void serialize(Serializer& serializer);
		virtual bool deserialize(Serializer& serializer, const std::string& identifier);

	protected:
		void onTransformUpdated();

	protected:
		ltbl::LightPointEmission* mLight;
};

} // namespace ke

#endif // KE_POINTLIGHTCOMPONENT_HPP