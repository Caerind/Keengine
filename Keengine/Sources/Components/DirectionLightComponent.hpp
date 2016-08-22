#ifndef DIRECTIONLIGHTCOMPONENT_HPP
#define DIRECTIONLIGHTCOMPONENT_HPP

#include "../Core/SceneComponent.hpp"
#include "../ExtLibs/LTBL2/LightDirectionEmission.hpp"

class DirectionLightComponent : public SceneComponent
{
	public:
		DirectionLightComponent();
		~DirectionLightComponent();

		void setColor(sf::Color color);
		sf::Color getColor() const;

	protected:
		ltbl::LightDirectionEmission::Ptr mLight;
};

#endif // DIRECTIONLIGHTCOMPONENT_HPP
