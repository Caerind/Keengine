#include "PointComponent.hpp"
#include "../Core/Scene.hpp"

namespace ke
{

PointComponent::PointComponent(Actor& actor)
	: SceneComponent(actor)
{
    setRadius(2.f);
    setColor(sf::Color::Red);
}

PointComponent::~PointComponent()
{
	onUnregister();
}

bool PointComponent::renderable() const
{
	return true;
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

void PointComponent::serialize(Serializer& serializer)
{
	SceneComponent::serialize(serializer);
	serializer.save("radius", getRadius());
	serializer.save("color", getColor());
}

bool PointComponent::deserialize(Serializer& serializer)
{
	float radius;
	sf::Color color;
	if (SceneComponent::deserialize(serializer) && serializer.load("radius", radius) && serializer.load("color", color))
	{
		setRadius(radius);
		setColor(color);
		return true;
	}
	return false;
}

void PointComponent::renderCurrent(sf::RenderTarget& target, sf::RenderStates states)
{
    target.draw(mPoint, states);
}

} // namespace ke