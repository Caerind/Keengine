#include "ShapeComponent.hpp"
#include "../Core/Scene.hpp"

namespace ke
{

ShapeComponent::ShapeComponent(Actor& actor) 
	: SceneComponent(actor)
{
}

void ShapeComponent::setPointCount(std::size_t points)
{
	mShape.setPointCount(points);
}

std::size_t ShapeComponent::getPointCount() const
{
	return mShape.getPointCount();
}

void ShapeComponent::setPoint(std::size_t index, sf::Vector2f const& point)
{
	mShape.setPoint(index, point);
}

sf::Vector2f ShapeComponent::getPoint(std::size_t index) const
{
	return mShape.getPoint(index);
}

void ShapeComponent::setOutlineThickness(float thickness)
{
	mShape.setOutlineThickness(thickness);
}

float ShapeComponent::getOutlineThickness() const
{
	return mShape.getOutlineThickness();
}

void ShapeComponent::setOutlineColor(sf::Color const& color)
{
	mShape.setOutlineColor(color);
}

sf::Color ShapeComponent::getOutlineColor() const
{
	return mShape.getOutlineColor();
}

void ShapeComponent::setFillColor(sf::Color const& color)
{
	mShape.setFillColor(color);
}

sf::Color ShapeComponent::getFillColor() const
{
	return mShape.getFillColor();
}

sf::FloatRect ShapeComponent::getLocalBounds()
{
	return getTransform().transformRect(mShape.getLocalBounds());
}

sf::FloatRect ShapeComponent::getGlobalBounds()
{
	return getWorldTransform().transformRect(mShape.getLocalBounds());
}

void ShapeComponent::serialize(Serializer & serializer)
{
	serializer.create(getType());
	serializer.save("id", getId());
	serializer.save("pos", getPosition());
	serializer.save("rot", getRotation());
	serializer.save("sca", getScale());
	serializer.save("z", getZ());
	serializer.save("visible", isVisible());
	serializer.save("fillColor", getFillColor());
	serializer.save("outColor", getOutlineColor());
	serializer.save("outThick", getOutlineThickness());
	std::vector<sf::Vector2f> points;
	for (std::size_t i = 0; i < getPointCount(); i++)
	{
		points.push_back(getPoint(i));
	}
	serializer.save("points", points);
	serializer.end();
}

bool ShapeComponent::deserialize(Serializer & serializer, const std::string & identifier)
{
	return false;
}

void ShapeComponent::renderCurrent(sf::RenderTarget& target, sf::RenderStates states)
{
	target.draw(mShape, states);
}

} // namespace ke