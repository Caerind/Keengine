#include "PointComponent.hpp"
#include "../Core/World.hpp"

PointComponent::PointComponent()
{
    setRadius(2.f);
    setColor(sf::Color::Red);
}

void PointComponent::setColor(sf::Color const& color)
{
    mPoint.setFillColor(color);
}

sf::Color PointComponent::getColor() const
{
    return mPoint.getFillColor();
}

void PointComponent::setRadius(float radius)
{
    mPoint.setRadius(radius);
    mPoint.setOrigin(radius, radius);
}

float PointComponent::getRadius() const
{
    return mPoint.getRadius();
}

void PointComponent::render(sf::RenderTarget& target)
{
    target.draw(mPoint, sf::RenderStates(getWorldTransform()));
}
