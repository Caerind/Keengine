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

		TYPE(PointComponent)

        PointComponent(Actor& actor);

        void setColor(sf::Color const& color);
        sf::Color getColor() const;

        void setRadius(float radius);
        float getRadius() const;

		virtual void serialize(Serializer& serializer);
		virtual bool deserialize(Serializer& serializer);

	private:
        virtual void renderCurrent(sf::RenderTarget& target, sf::RenderStates states);

    private:
        sf::CircleShape mPoint;
};

} // namespace ke

#endif // KE_POINTCOMPONENT_HPP
