#include "LightShapeComponent.hpp"
#include "../Core/Scene.hpp"

namespace ke
{

LightShapeComponent::LightShapeComponent(Actor& actor)
	: SceneComponent(actor)
	, mPoints()
	, mLightShape(nullptr)
{
}

LightShapeComponent::~LightShapeComponent()
{
	onUnregister();
}

void LightShapeComponent::onRegister()
{
	if (!isRegistered())
	{
		if (getScene().useLight() && getScene().getLights() != nullptr && mLightShape == nullptr)
		{
			mLightShape = getScene().getLights()->createLightShape();
			if (mLightShape != nullptr)
			{
				mLightShape->setTurnedOn(isVisible());
			}
		}
		SceneComponent::onRegister();
	}
}

void LightShapeComponent::onUnregister()
{
	if (isRegistered())
	{
		if (getScene().useLight() && getScene().getLights() != nullptr && mLightShape != nullptr)
		{
			getScene().getLights()->removeShape(mLightShape);
			mLightShape = nullptr;
		}
		SceneComponent::onUnregister();
	}
}

void LightShapeComponent::setPointCount(std::size_t points)
{
	mPoints.resize(points, sf::Vector2f());
	if (mLightShape != nullptr)
	{
		mLightShape->setPointCount(points);
	}
}

std::size_t LightShapeComponent::getPointCount() const
{
	return mPoints.size();
}

void LightShapeComponent::setPoint(std::size_t index, sf::Vector2f const& point)
{
	mPoints[index] = point;
	if (mLightShape != nullptr)
	{
		mLightShape->setPoint(index, point);
	}
}

sf::Vector2f LightShapeComponent::getPoint(std::size_t index) const
{
	return mPoints[index];
}

sf::FloatRect LightShapeComponent::getLocalBounds()
{
	if (mLightShape != nullptr)
	{
		// TODO : Rect from points
	}
	return sf::FloatRect();
}

sf::FloatRect LightShapeComponent::getGlobalBounds()
{
	if (mLightShape != nullptr)
	{
		// TODO : Rect from points
	}
	return sf::FloatRect();
}

void LightShapeComponent::setPoints(const std::vector<sf::Vector2f>& points)
{
	mPoints = points;
	if (mLightShape != nullptr)
	{
		std::size_t count = mPoints.size();
		mLightShape->setPointCount(count);
		for (std::size_t i = 0; i < count; i++)
		{
			mLightShape->setPoint(i, points[i]);
		}
	}
}

std::vector<sf::Vector2f> LightShapeComponent::getPoints() const
{
	return mPoints;
}

void LightShapeComponent::setOn(bool on)
{
	if (mLightShape != nullptr)
	{
		mLightShape->setTurnedOn(on);
	}
}

bool LightShapeComponent::isOn() const
{
	if (mLightShape != nullptr)
	{
		return mLightShape->isTurnedOn();
	}
	return false;
}

void LightShapeComponent::serialize(Serializer& serializer)
{
	SceneComponent::serialize(serializer);
	serializer.save("on", isOn());
	serializer.save("points", getPoints());
}

bool LightShapeComponent::deserialize(Serializer& serializer)
{
	bool on;
	std::vector<sf::Vector2f> points;
	if (SceneComponent::deserialize(serializer) && serializer.load("on", on) && serializer.load("points", points))
	{
		setOn(on);
		setPoints(points);
		return true;
	}
	return false;
}

void LightShapeComponent::onTransformNotified()
{
	if (mLightShape != nullptr)
	{
		mLightShape->setPosition(getWorldPosition());
		mLightShape->setRotation(getRotation());
		mLightShape->setScale(getScale());
	}
}

} // namespace ke