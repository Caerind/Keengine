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
		mLight = getScene().getLights().createLightPointEmission();

		Texture& texture = getApplication().getResource<Texture>("pointLightTexture");

		mLight->setOrigin(sf::Vector2f(texture.getSize().x * 0.5f, texture.getSize().y * 0.5f));
		mLight->setTexture(texture);

		mLight->setPosition(getWorldPosition());
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
		mLight->setColor(color);
	}
}

sf::Color PointLightComponent::getColor() const
{
	if (mLight != nullptr)
	{
		return mLight->getColor();
	}
	return sf::Color();
}

void PointLightComponent::setIntensity(float intensity)
{
	if (mLight != nullptr)
	{
		mLight->setScale(intensity * sf::Vector2f(1.f, 1.f));
	}
}

float PointLightComponent::getIntensity() const
{
	if (mLight != nullptr)
	{
		return mLight->getScale().x;
	}
	return 1.f;
}

void PointLightComponent::setOn(bool on)
{
	if (mLight != nullptr)
	{
		mLight->setTurnedOn(on);
	}
}

bool PointLightComponent::isOn() const
{
	if (mLight != nullptr)
	{
		return mLight->isTurnedOn();
	}
	return false;
}

void PointLightComponent::onTransformUpdated()
{
	if (mLight != nullptr)
	{
		mLight->setPosition(getWorldPosition());
	}
}

} // namespace ke
