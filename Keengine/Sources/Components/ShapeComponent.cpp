#include "ShapeComponent.hpp"

namespace ke
{

ShapeComponent::ShapeComponent(Actor& actor)
	: SceneComponent(actor)
	, mPoints()
	, mShape()
{
	mUpdatable = false;
}

void ShapeComponent::onRegister()
{
	mShape.setFillColor(sf::Color::Transparent);
	mShape.setOutlineColor(sf::Color::Transparent);
}

void ShapeComponent::onUnregister()
{
}

void ShapeComponent::setPointCount(std::size_t points)
{
	mPoints.resize(points, sf::Vector2f());
	mShape.setPointCount(points);
}

std::size_t ShapeComponent::getPointCount() const
{
	return mPoints.size();
}

void ShapeComponent::setPoint(std::size_t index, sf::Vector2f const& point)
{
	mPoints[index] = point;
	mShape.setPoint(index, point);
}

sf::Vector2f ShapeComponent::getPoint(std::size_t index) const
{
	return mPoints[index];
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

void ShapeComponent::setPoints(const std::vector<sf::Vector2f>& points)
{
	mPoints = points;
	std::size_t count = points.size();
	mShape.setPointCount(count);
	for (std::size_t i = 0; i < count; i++)
	{
		mShape.setPoint(i, points[i]);
	}
}

std::vector<sf::Vector2f> ShapeComponent::getPoints() const
{
	return mPoints;
}

void ShapeComponent::serialize(Serializer& serializer)
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
	serializer.save("points", getPoints());
	serializer.end();
}

bool ShapeComponent::deserialize(Serializer& serializer)
{
	return false;
}

void ShapeComponent::renderCurrent(sf::RenderTarget& target, sf::RenderStates states)
{
	target.draw(mShape, states);
}

} // namespace ke