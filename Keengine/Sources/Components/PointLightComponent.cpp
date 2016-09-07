#include "PointLightComponent.hpp"
#include "../Core/Scene.hpp"

namespace ke
{

PointLightComponent::PointLightComponent(Actor& actor)
	: SceneComponent(actor)
	, mLight(nullptr)
{
}

void PointLightComponent::onRegister()
{
	if (getScene().useLight() && mLight == nullptr)
	{
		mLight = getScene().getLights().createLightPoint();

		Texture& texture = getApplication().getResource<Texture>("pointLightTexture");

		mLight->_emissionSprite.setOrigin(sf::Vector2f(texture.getSize().x * 0.5f, texture.getSize().y * 0.5f));
		mLight->_emissionSprite.setTexture(texture);

		mLight->_emissionSprite.setPosition(getWorldPosition());
	}
}

void PointLightComponent::onUnregister()
{
	if (getScene().useLight() && mLight != nullptr)
	{
		getScene().getLights().removeLight(mLight);
		mLight = nullptr;
	}
}

void PointLightComponent::setColor(sf::Color color)
{
	if (mLight != nullptr)
	{
		mLight->_emissionSprite.setColor(color);
	}
}

sf::Color PointLightComponent::getColor() const
{
	if (mLight != nullptr)
	{
		return mLight->_emissionSprite.getColor();
	}
	return sf::Color();
}

void PointLightComponent::setIntensity(float intensity)
{
	if (mLight != nullptr)
	{
		mLight->_emissionSprite.setScale(intensity * sf::Vector2f(1.f, 1.f));
	}
}

float PointLightComponent::getIntensity() const
{
	if (mLight != nullptr)
	{
		return mLight->_emissionSprite.getScale().x;
	}
	return 1.f;
}

void PointLightComponent::onTransformUpdated()
{
	if (mLight != nullptr)
	{
		mLight->_emissionSprite.setPosition(getWorldPosition());
	}
}

} // namespace ke
