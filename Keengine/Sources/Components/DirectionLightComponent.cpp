#include "DirectionLightComponent.hpp"
#include "../Core/Scene.hpp"
#include "../Maths/Vector2.hpp"

namespace ke
{

DirectionLightComponent::DirectionLightComponent(Actor& actor)
	: SceneComponent(actor)
	, mLight(nullptr)
{
	mUpdatable = false;
	mVisible = false;
}

void DirectionLightComponent::onRegister()
{
	if (getScene().useLight() && mLight == nullptr)
	{
		mLight = getScene().getLights().createLightDirectionEmission();
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
		mLight->setColor(color);
	}
}

sf::Color DirectionLightComponent::getColor() const
{
	if (mLight != nullptr)
	{
		return mLight->getColor();
	}
	return sf::Color();
}

void DirectionLightComponent::setAngle(float angle)
{
	if (mLight != nullptr)
	{
		mLight->setCastAngle(angle);
	}
}

float DirectionLightComponent::getAngle() const
{
	if (mLight != nullptr)
	{
		return mLight->getCastAngle();
	}
	return 0.f;
}

void DirectionLightComponent::setDirection(sf::Vector2f const& vector)
{
	if (mLight != nullptr)
	{
		mLight->setCastDirection(vector);
	}
}

sf::Vector2f DirectionLightComponent::getDirection() const
{
	if (mLight != nullptr)
	{
		return mLight->getCastDirection();
	}
	return sf::Vector2f();
}

void DirectionLightComponent::serialize(Serializer& serializer)
{
	serializer.create(getType());
	serializer.save("id", getId());
	serializer.save("angle", getAngle());
	serializer.save("color", getColor());
	serializer.end();
}

bool DirectionLightComponent::deserialize(Serializer & serializer, const std::string & identifier)
{
	return false;
}

} // namespace ke