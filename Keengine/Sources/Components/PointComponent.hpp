#ifndef KE_POINTCOMPONENT_HPP
#define KE_POINTCOMPONENT_HPP

#include <SFML/Graphics/CircleShape.hpp>

#include "../Core/SceneComponent.hpp"

namespace ke
{

class PointComponent : public SceneComponent
{
    public:
		typedef std::shared_ptr<PointComponent> Ptr;

        PointComponent(Actor& actor);

        void setColor(sf::Color const& color);
        sf::Color getColor() const;

        void setRadius(float radius);
        float getRadius() const;

	private:
        virtual void renderCurrent(sf::RenderTarget& target, sf::RenderStates states);

    private:
        sf::CircleShape mPoint;
};

} // namespace ke

#endif // KE_POINTCOMPONENT_HPP
