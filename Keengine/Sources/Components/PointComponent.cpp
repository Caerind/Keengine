#include "PointComponent.hpp"
#include "../Core/Scene.hpp"

namespace ke
{

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

void PointComponent::renderCurrent(sf::RenderTarget& target, sf::RenderStates states)
{
    target.draw(mPoint, states);
}

} // namespace ke