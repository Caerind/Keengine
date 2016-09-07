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
		mLightShape = getScene().getLights().createShape();
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
		mLightShape->_shape.setPointCount(points);
	}
}

std::size_t LightShapeComponent::getPointCount() const
{
	if (mLightShape != nullptr)
	{
		return mLightShape->_shape.getPointCount();
	}
	return 0;
}

void LightShapeComponent::setPoint(std::size_t index, sf::Vector2f const& point)
{
	if (mLightShape != nullptr)
	{
		mLightShape->_shape.setPoint(index, point);
	}
}

sf::Vector2f LightShapeComponent::getPoint(std::size_t index) const
{
	if (mLightShape != nullptr)
	{
		return mLightShape->_shape.getPoint(index);
	}
	return sf::Vector2f();
}

void LightShapeComponent::setOutlineThickness(float thickness)
{
	if (mLightShape != nullptr)
	{
		mLightShape->_shape.setOutlineThickness(thickness);
	}
}

float LightShapeComponent::getOutlineThicnkess() const
{
	if (mLightShape != nullptr)
	{
		return mLightShape->_shape.getOutlineThickness();
	}
	return 0.f;
}

sf::FloatRect LightShapeComponent::getLocalBounds()
{
	if (mLightShape != nullptr)
	{
		return getTransform().transformRect(mLightShape->_shape.getLocalBounds());
	}
	return sf::FloatRect();
}

sf::FloatRect LightShapeComponent::getGlobalBounds()
{
	if (mLightShape != nullptr)
	{
		return getWorldTransform().transformRect(mLightShape->_shape.getLocalBounds());
	}
	return sf::FloatRect();
}

void LightShapeComponent::onTransformUpdated()
{
	if (mLightShape != nullptr)
	{
		mLightShape->_shape.setPosition(getWorldPosition());
	}
}

} // namespace ke