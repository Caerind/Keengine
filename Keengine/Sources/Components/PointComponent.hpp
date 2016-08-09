#ifndef POINTCOMPONENT_HPP
#define POINTCOMPONENT_HPP

#include <SFML/Graphics/CircleShape.hpp>

#include "../Core/PrimitiveComponent.hpp"

class PointComponent : public PrimitiveComponent
{
    public:
        PointComponent();

        void setColor(sf::Color const& color);
        sf::Color getColor() const;

        void setRadius(float radius);
        float getRadius() const;

        void render(sf::RenderTarget& target);

    private:
        sf::CircleShape mPoint;
};

#endif // POINTCOMPONENT_HPP
