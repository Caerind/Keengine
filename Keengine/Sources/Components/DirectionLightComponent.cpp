#include "DirectionLightComponent.hpp"
#include "../Core/World.hpp"

DirectionLightComponent::DirectionLightComponent()
{
	mLight = getWorld().getLights().createLightDirection();

	Texture& texture = getWorld().getResource<Texture>("directionLightTexture");

	mLight->_emissionSprite.setOrigin(sf::Vector2f(texture.getSize().x * 0.5f, texture.getSize().y * 0.5f));
	mLight->_emissionSprite.setTexture(texture);

	mLight->_emissionSprite.setPosition(getWorldPosition()); // TODO : Position
}

DirectionLightComponent::~DirectionLightComponent()
{
	getWorld().getLights().removeLight(mLight);
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
