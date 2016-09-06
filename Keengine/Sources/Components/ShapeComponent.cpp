#include "ShapeComponent.hpp"
#include "../Core/Scene.hpp"

namespace ke
{

ShapeComponent::ShapeComponent() : mLightShape(nullptr)
{
}

ShapeComponent::~ShapeComponent()
{
	if (isRegistered())
	{
		onUnregister();
	}
}

void ShapeComponent::onRegister()
{
	Scene* scene = getScene();
	if (scene != nullptr)
	{
		//mLightShape = scene->getLights().createShape();
	}
}

void ShapeComponent::onUnregister()
{
	Scene* scene = getScene();
	if (scene != nullptr)
	{
		//scene->getLights().removeShape(mLightShape);
	}
}

void ShapeComponent::setPointCount(std::size_t points)
{
	mShape.setPointCount(points);
	if (mLightShape != nullptr)
	{
		mLightShape->_shape.setPointCount(points);
	}
}

std::size_t ShapeComponent::getPointCount() const
{
	return mShape.getPointCount();
}

void ShapeComponent::setPoint(std::size_t index, sf::Vector2f const& point)
{
	mShape.setPoint(index, point);
	if (mLightShape != nullptr)
	{
		mLightShape->_shape.setPoint(index, point);
	}
}

sf::Vector2f ShapeComponent::getPoint(std::size_t index) const
{
	return mShape.getPoint(index);
}

void ShapeComponent::setOutlineThickness(float thickness)
{
	mShape.setOutlineThickness(thickness);
	if (mLightShape != nullptr)
	{
		mLightShape->_shape.setOutlineThickness(thickness);
	}
}

float ShapeComponent::getOutlineThicnkess() const
{
	return mShape.getOutlineThickness();
}

void ShapeComponent::setOutlineColor(sf::Color const& color)
{
	mShape.setOutlineColor(color);
	if (mLightShape != nullptr)
	{
		mLightShape->_shape.setOutlineColor(color);
	}
}

sf::Color ShapeComponent::getOutlineColor() const
{
	return mShape.getOutlineColor();
}

void ShapeComponent::setFillColor(sf::Color const& color)
{
	mShape.setFillColor(color);
	if (mLightShape != nullptr)
	{
		mLightShape->_shape.setFillColor(color);
	}
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

void ShapeComponent::renderCurrent(sf::RenderTarget& target, sf::RenderStates states)
{
	target.draw(mShape, states);
}

} // namespace ke