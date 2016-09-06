#include "PointLightComponent.hpp"
#include "../Core/Scene.hpp"

namespace ke
{

PointLightComponent::PointLightComponent() : mLight(nullptr)
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
	Scene* scene = getScene();
	if (scene != nullptr)
	{
		/*
		mLight = scene->getLights().createLightPoint();

		Texture& texture = getApplication().getResource<Texture>("pointLightTexture");

		mLight->_emissionSprite.setOrigin(sf::Vector2f(texture.getSize().x * 0.5f, texture.getSize().y * 0.5f));
		mLight->_emissionSprite.setTexture(texture);

		mLight->_emissionSprite.setPosition(getWorldPosition());
		*/
	}
}

void PointLightComponent::onUnregister()
{
	Scene* scene = getScene();
	if (scene != nullptr)
	{
		//scene->getLights().removeLight(mLight);
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
