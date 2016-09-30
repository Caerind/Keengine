#include "ShapeComponent.hpp"
#include "../Core/Scene.hpp"

namespace ke
{

LightShapeComponent::LightShapeComponent(Actor& actor)
	: SceneComponent(actor)
	, mLightShape(nullptr)
{
}

void LightShapeComponent::onRegister()
{
	if (getScene().useLight() && mLightShape == nullptr)
	{
		mLightShape = getScene().getLights().createLightShape();
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
	if (mLightShape != nullptr)
	{
		mLightShape->setPointCount(points);
	}
}

std::size_t LightShapeComponent::getPointCount() const
{
	if (mLightShape != nullptr)
	{
		return mLightShape->getPointCount();
	}
	return 0;
}

void LightShapeComponent::setPoint(std::size_t index, sf::Vector2f const& point)
{
	if (mLightShape != nullptr)
	{
		mLightShape->setPoint(index, point);
	}
}

sf::Vector2f LightShapeComponent::getPoint(std::size_t index) const
{
	if (mLightShape != nullptr)
	{
		return mLightShape->getPoint(index);
	}
	return sf::Vector2f();
}

sf::FloatRect LightShapeComponent::getLocalBounds()
{
	if (mLightShape != nullptr)
	{
		//return getTransform().transformRect(mLightShape->getLocalBounds());
	}
	return sf::FloatRect();
}

sf::FloatRect LightShapeComponent::getGlobalBounds()
{
	if (mLightShape != nullptr)
	{
		//return getWorldTransform().transformRect(mLightShape->getLocalBounds());
	}
	return sf::FloatRect();
}

void LightShapeComponent::onTransformUpdated()
{
	if (mLightShape != nullptr)
	{
		mLightShape->setPosition(getWorldPosition());
	}
}

} // namespace ke