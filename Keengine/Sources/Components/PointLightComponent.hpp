#ifndef POINTLIGHTCOMPONENT_HPP
#define POINTLIGHTCOMPONENT_HPP

#include "../Core/SceneComponent.hpp"
#include "../ExtLibs/LTBL2/LightPointEmission.hpp"

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

#endif // POINTLIGHTCOMPONENT_HPP