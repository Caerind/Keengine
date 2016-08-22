#ifndef KE_POINTLIGHTCOMPONENT_HPP
#define KE_POINTLIGHTCOMPONENT_HPP

#include "../Core/SceneComponent.hpp"
#include "../ExtLibs/LTBL2/LightPointEmission.hpp"

namespace ke
{

class PointLightComponent : public SceneComponent
{
	public:
		PointLightComponent();
		~PointLightComponent();

		void setColor(sf::Color color);
		sf::Color getColor() const;

		void setIntensity(float intensity);
		float getIntensity() const;

	protected:
		void onPositionChanged();

	protected:
		ltbl::LightPointEmission::Ptr mLight;
};

} // namespace ke

#endif // KE_POINTLIGHTCOMPONENT_HPP