#include "PointLightComponent.hpp"
#include "../Core/Scene.hpp"

namespace ke
{

PointLightComponent::PointLightComponent(Actor& actor)
	: SceneComponent(actor)
	, mLight(nullptr)
	, mTexture("")
{
	mUpdatable = false;
	mVisible = false;
}

void PointLightComponent::onRegister()
{
	if (getScene().useLight() && mLight == nullptr)
	{
		mLight = getScene().getLights().createLightPointEmission();
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
	serializer.create(getType());
	serializer.save("id", getId());
	serializer.save("pos", getPosition());
	serializer.save("rot", getRotation());
	serializer.save("sca", getScale());
	serializer.save("z", getZ());
	serializer.save("texture", getTexture());
	serializer.save("color", getColor());
	serializer.save("intensity", getIntensity());
	serializer.save("on", isOn());
	serializer.end();
}

bool PointLightComponent::deserialize(Serializer& serializer)
{
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
