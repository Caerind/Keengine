#include "DirectionLightComponent.hpp"
#include "../Core/Scene.hpp"
#include "../Maths/Vector2.hpp"

namespace ke
{

DirectionLightComponent::DirectionLightComponent(Actor& actor)
	: SceneComponent(actor)
	, mLight(nullptr)
{
}

void DirectionLightComponent::onRegister()
{
	if (getScene().useLight() && mLight == nullptr)
	{
		mLight = getScene().getLights().createLightDirection();

		Texture& texture = getApplication().getResource<Texture>("directionLightTexture");

		mLight->_emissionSprite.setOrigin(sf::Vector2f(texture.getSize().x * 0.5f, texture.getSize().y * 0.5f));
		mLight->_emissionSprite.setTexture(texture);

		mLight->_emissionSprite.setPosition(getWorldPosition());
	}
}

void DirectionLightComponent::onUnregister()
{
	if (getScene().useLight() && mLight != nullptr)
	{
		getScene().getLights().removeLight(mLight);
		mLight = nullptr;
	}
}

void DirectionLightComponent::setColor(sf::Color color)
{
	if (mLight != nullptr)
	{
		mLight->_emissionSprite.setColor(color);
	}
}

sf::Color DirectionLightComponent::getColor() const
{
	if (mLight != nullptr)
	{
		return mLight->_emissionSprite.getColor();
	}
	return sf::Color();
}

void DirectionLightComponent::setIntensity(float intensity)
{
	if (mLight != nullptr)
	{
		mLight->_emissionSprite.setScale(intensity * sf::Vector2f(1.f, 1.f));
	}
}

float DirectionLightComponent::getIntensity() const
{
	if (mLight != nullptr)
	{
		return mLight->_emissionSprite.getScale().x;
	}
	return 1.f;
}

void DirectionLightComponent::setAngle(float angle)
{
	if (mLight != nullptr)
	{
		mLight->_castDirection = polarVector(1.f, angle);
	}
}

float DirectionLightComponent::getAngle() const
{
	if (mLight != nullptr)
	{
		return getPolarAngle(mLight->_castDirection);
	}
	return 0.f;
}

void DirectionLightComponent::setDirection(sf::Vector2f const& vector)
{
	if (mLight != nullptr)
	{
		mLight->_castDirection = ltbl::vectorNormalize(vector);
	}
}

sf::Vector2f DirectionLightComponent::getDirection() const
{
	if (mLight != nullptr)
	{
		return mLight->_castDirection;
	}
	return sf::Vector2f();
}

void DirectionLightComponent::onTransformUpdated()
{
	if (mLight != nullptr)
	{
		mLight->_emissionSprite.setPosition(getWorldPosition());
	}
}

} // namespace ke