#include "PointLightComponent.hpp"
#include "../Core/Scene.hpp"

namespace ke
{

PointLightComponent::PointLightComponent(Actor& actor)
	: SceneComponent(actor)
	, mLight(nullptr)
	, mTexture("")
{
}

PointLightComponent::~PointLightComponent()
{
	onUnregister();
}

void PointLightComponent::onRegister()
{
	if (!isRegistered())
	{
		if (getScene().useLight() && getScene().getLights() != nullptr && mLight == nullptr)
		{
			mLight = getScene().getLights()->createLightPointEmission();
		}
		SceneComponent::onRegister();
	}
}

void PointLightComponent::onUnregister()
{
	if (isRegistered())
	{
		if (getScene().useLight() && getScene().getLights() != nullptr && mLight != nullptr)
		{
			getScene().getLights()->removeLight(mLight);
			mLight = nullptr;
		}
		SceneComponent::onUnregister();
	}
}

void PointLightComponent::setTexture(const std::string& texture)
{
	if (getApplication().hasResource(texture) && mLight != nullptr)
	{
		if (getApplication().isResourceLoaded(texture))
		{
			mTexture = texture;
			mLight->setTexture(getApplication().getResource<Texture>(texture));
			mLight->setPosition(getWorldPosition());
		}
	}
}

std::string PointLightComponent::getTexture() const
{
	return mTexture;
}

void PointLightComponent::setOrigin(const sf::Vector2f& origin)
{
	if (mLight != nullptr)
	{
		mLight->setOrigin(origin);
	}
}

void PointLightComponent::setOrigin(float x, float y)
{
	if (mLight != nullptr)
	{
		mLight->setOrigin(sf::Vector2f(x, y));
	}
}

sf::Vector2f PointLightComponent::getOrigin() const
{
	if (mLight != nullptr)
	{
		return mLight->getOrigin();
	}
	return sf::Vector2f();
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

void PointLightComponent::serialize(Serializer& serializer)
{
	SceneComponent::serialize(serializer);
	serializer.save("texture", getTexture());
	serializer.save("color", getColor());
	serializer.save("intensity", getIntensity());
	serializer.save("on", isOn());
}

bool PointLightComponent::deserialize(Serializer& serializer)
{
	std::string texture;
	sf::Color color;
	float intensity;
	bool on;
	if (SceneComponent::deserialize(serializer)
		&& serializer.load("texture", texture)
		&& serializer.load("color", color)
		&& serializer.load("intensity", intensity)
		&& serializer.load("on", on))
	{
		setTexture(texture);
		setColor(color);
		setIntensity(intensity);
		setOn(on);
		return true;
	}
	return false;
}

void PointLightComponent::onTransformNotified()
{
	if (mLight != nullptr)
	{
		mLight->setPosition(getWorldPosition());
	}
}

} // namespace ke
