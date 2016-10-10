#include "LightShapeComponent.hpp"
#include "../Core/Scene.hpp"

namespace ke
{

LightShapeComponent::LightShapeComponent(Actor& actor)
	: SceneComponent(actor)
	, mPoints()
	, mLightShape(nullptr)
{
	mUpdatable = false;
}

void LightShapeComponent::onRegister()
{
	if (getScene().useLight() && mLightShape == nullptr)
	{
		mLightShape = getScene().getLights().createLightShape();
		if (mLightShape != nullptr)
		{
			mLightShape->setTurnedOn(isVisible());
		}
	}
}

void LightShapeComponent::onUnregister()
{
	if (getScene().useLight() && mLightShape != nullptr)
	{
		getScene().getLights().removeShape(mLightShape);
		mLightShape = nullptr;
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
	serializer.create(getType());
	serializer.save("id", getId());
	serializer.save("pos", getPosition());
	serializer.save("rot", getRotation());
	serializer.save("sca", getScale());
	serializer.save("z", getZ());
	serializer.save("on", isOn());
	serializer.save("points", getPoints());
	serializer.end();
}

bool LightShapeComponent::deserialize(Serializer& serializer)
{
	return false;
}

void LightShapeComponent::onTransformUpdated()
{
	if (mLightShape != nullptr)
	{
		mLightShape->setPosition(getWorldPosition());
		mLightShape->setRotation(getRotation());
		mLightShape->setScale(getScale());
	}
}

} // namespace ke