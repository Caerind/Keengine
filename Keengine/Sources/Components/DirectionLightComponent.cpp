#include "DirectionLightComponent.hpp"
#include "../Core/World.hpp"
#include "../Maths/Vector2.hpp"

namespace ke
{

DirectionLightComponent::DirectionLightComponent()
{
}

DirectionLightComponent::~DirectionLightComponent()
{
}

void DirectionLightComponent::onRegister()
{
	World* world = getWorld();
	if (world != nullptr)
	{
		mLight = world->getLights().createLightDirection();

		Texture& texture = world->getResource<Texture>("directionLightTexture");

		mLight->_emissionSprite.setOrigin(sf::Vector2f(texture.getSize().x * 0.5f, texture.getSize().y * 0.5f));
		mLight->_emissionSprite.setTexture(texture);

		mLight->_emissionSprite.setPosition(getWorldPosition());
	}
}

void DirectionLightComponent::onUnregister()
{
	World* world = getWorld();
	if (world != nullptr)
	{
		world->getLights().removeLight(mLight);
	}
}

void DirectionLightComponent::setColor(sf::Color color)
{
	if (mLight)
	{
		mLight->_emissionSprite.setColor(color);
	}
}

sf::Color DirectionLightComponent::getColor() const
{
	if (mLight)
	{
		return mLight->_emissionSprite.getColor();
	}
	return sf::Color();
}

void DirectionLightComponent::setIntensity(float intensity)
{
	mLight->_emissionSprite.setScale(intensity * sf::Vector2f(1.f, 1.f));
}

float DirectionLightComponent::getIntensity() const
{
	return mLight->_emissionSprite.getScale().x;
}

void DirectionLightComponent::setAngle(float angle)
{
	mLight->_castDirection = polarVector(1.f, angle);
}

float DirectionLightComponent::getAngle() const
{
	return getPolarAngle(mLight->_castDirection);
}

void DirectionLightComponent::setDirection(sf::Vector2f const & vector)
{
	mLight->_castDirection = ltbl::vectorNormalize(vector);
}

sf::Vector2f DirectionLightComponent::getDirection() const
{
	return mLight->_castDirection;
}

void DirectionLightComponent::onTransformUpdated()
{
	mLight->_emissionSprite.setPosition(getWorldPosition());
}

} // namespace ke