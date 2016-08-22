#include "PointLightComponent.hpp"
#include "../Core/World.hpp"

PointLightComponent::PointLightComponent()
{
	mLight = getWorld().getLights().createLightPoint();

	Texture& texture = getWorld().getResource<Texture>("pointLightTexture");

	mLight->_emissionSprite.setOrigin(sf::Vector2f(texture.getSize().x * 0.5f, texture.getSize().y * 0.5f));
	mLight->_emissionSprite.setTexture(texture);

	mLight->_emissionSprite.setPosition(getWorldPosition());
}

PointLightComponent::~PointLightComponent()
{
	getWorld().getLights().removeLight(mLight);
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

void PointLightComponent::onPositionChanged()
{
	mLight->_emissionSprite.setPosition(getWorldPosition());
}
