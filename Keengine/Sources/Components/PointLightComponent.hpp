#ifndef KE_POINTLIGHTCOMPONENT_HPP
#define KE_POINTLIGHTCOMPONENT_HPP

#include "../Core/SceneComponent.hpp"
#include "../ExtLibs/LTBL2/LightPointEmission.hpp"

namespace ke
{

class PointLightComponent : public SceneComponent
{
	public:
		typedef std::shared_ptr<PointLightComponent> Ptr;

		PointLightComponent(Actor& actor);

		void onRegister();
		void onUnregister();

		void setColor(sf::Color color);
		sf::Color getColor() const;

		void setIntensity(float intensity);
		float getIntensity() const;

		void setOn(bool on);
		bool isOn() const;

	protected:
		void onTransformUpdated();

	protected:
		ltbl::LightPointEmission::Ptr mLight;
};

} // namespace ke

#endif // KE_POINTLIGHTCOMPONENT_HPP