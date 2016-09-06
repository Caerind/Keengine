#include "PointLightComponent.hpp"
#include "../Core/World.hpp"

namespace ke
{

PointLightComponent::PointLightComponent()
{
}

PointLightComponent::~PointLightComponent()
{
	if (isRegistered())
	{
		onUnregister();
	}
}

void PointLightComponent::onRegister()
{
	World* world = getWorld();
	if (world != nullptr)
	{
		mLight = world->getLights().createLightPoint();

		Texture& texture = world->getResource<Texture>("pointLightTexture");

		mLight->_emissionSprite.setOrigin(sf::Vector2f(texture.getSize().x * 0.5f, texture.getSize().y * 0.5f));
		mLight->_emissionSprite.setTexture(texture);

		mLight->_emissionSprite.setPosition(getWorldPosition());
	}
}

void PointLightComponent::onUnregister()
{
	World* world = getWorld();
	if (world != nullptr)
	{
		world->getLights().removeLight(mLight);
	}
}

void PointLightComponent::setColor(sf::Color color)
{
	if (mLight)
	{
		mLight->_emissionSprite.setColor(color);
	}
}

sf::Color PointLightComponent::getColor() const
{
	if (mLight)
	{
		return mLight->_emissionSprite.getColor();
	}
	return sf::Color();
}

void PointLightComponent::setIntensity(float intensity)
{
	if (mLight)
	{
		mLight->_emissionSprite.setScale(intensity * sf::Vector2f(1.f, 1.f));
	}
}

float PointLightComponent::getIntensity() const
{
	if (mLight)
	{
		return mLight->_emissionSprite.getScale().x;
	}
	return 1.f;
}

void PointLightComponent::onTransformUpdated()
{
	mLight->_emissionSprite.setPosition(getWorldPosition());
}

} // namespace ke
