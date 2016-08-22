#ifndef KE_DIRECTIONLIGHTCOMPONENT_HPP
#define KE_DIRECTIONLIGHTCOMPONENT_HPP

#include "../Core/SceneComponent.hpp"
#include "../ExtLibs/LTBL2/LightDirectionEmission.hpp"

namespace ke
{

class DirectionLightComponent : public SceneComponent
{
	public:
		DirectionLightComponent();
		~DirectionLightComponent();

		void setColor(sf::Color color);
		sf::Color getColor() const;

		void setIntensity(float intensity);
		float getIntensity() const;

		void setAngle(float angle);
		float getAngle() const;
		void setDirection(sf::Vector2f const& vector);
		sf::Vector2f getDirection() const;

	protected:
		void onPositionChanged();

	protected:
		ltbl::LightDirectionEmission::Ptr mLight;
};

} // namespace ke

#endif // KE_DIRECTIONLIGHTCOMPONENT_HPP
