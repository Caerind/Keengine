#include "Component.hpp"

#include "Actor.hpp"
#include "World.hpp"

namespace ke
{

Component::Component()
	: mRegistered(false)
	, mActor(nullptr)
	, mUpdatable(true)
{
}

Component::~Component()
{
}

void Component::registerComponent(Actor* actor)
{
	if (actor != nullptr)
	{
		mActor = actor;
		mRegistered = true;
		onRegister();
	}
}

void Component::unregisterComponent(Actor* actor)
{
	if (actor == nullptr && mActor != nullptr)
	{
		unregisterComponent(mActor);
	}
	if (actor != nullptr)
	{
		onUnregister();
		mActor = nullptr;
		mRegistered = false;
	}
}

bool Component::isRegistered() const
{
	return mRegistered;
}

void Component::onRegister()
{
}

void Component::onUnregister()
{
}

bool Component::isUpdatable() const
{
	return mUpdatable;
}

void Component::update(sf::Time dt)
{
}

sf::Vector2f Component::getActorPosition() const
{
	if (mActor != nullptr)
	{
		return mActor->getPosition();
	}
	else
	{
		getWorld().getLog() << "Invalid actor";
	}
	return sf::Vector2f();
}

void Component::setActorPosition(sf::Vector2f const& position)
{
	if (mActor != nullptr)
	{
		mActor->setPosition(position);
	}
	else
	{
		getWorld().getLog() << "Invalid actor";
	}
}

void Component::moveActor(sf::Vector2f const& movement)
{
	if (mActor != nullptr)
	{
		mActor->move(movement);
	}
	else
	{
		getWorld().getLog() << "Invalid actor";
	}
}

float Component::getActorRotation() const
{
	if (mActor != nullptr)
	{
		return mActor->getRotation();
	}
	else
	{
		getWorld().getLog() << "Invalid actor";
	}
	return 0.f;
}

void Component::setActorRotation(float rotation)
{
	if (mActor != nullptr)
	{
		mActor->setRotation(rotation);
	}
	else
	{
		getWorld().getLog() << "Invalid actor";
	}
}

void Component::rotateActor(float rotation)
{
	if (mActor != nullptr)
	{
		mActor->rotate(rotation);
	}
	else
	{
		getWorld().getLog() << "Invalid actor";
	}
}

sf::Vector2f Component::getActorScale() const
{
	if (mActor != nullptr)
	{
		return mActor->getScale();
	}
	else
	{
		getWorld().getLog() << "Invalid actor";
	}
	return sf::Vector2f();
}

void Component::setActorScale(sf::Vector2f const& scale)
{
	if (mActor != nullptr)
	{
		mActor->setScale(scale);
	}
	else
	{
		getWorld().getLog() << "Invalid actor";
	}
}

void Component::scaleActor(sf::Vector2f const& scale)
{
	if (mActor != nullptr)
	{
		mActor->scale(scale);
	}
	else
	{
		getWorld().getLog() << "Invalid actor";
	}
}

float Component::getActorZ() const
{
	if (mActor != nullptr)
	{
		return mActor->getZ();
	}
	else
	{
		getWorld().getLog() << "Invalid actor";
	}
	return 0.f;
}

void Component::setActorZ(float z)
{
	if (mActor != nullptr)
	{
		mActor->setZ(z);
	}
	else
	{
		getWorld().getLog() << "Invalid actor";
	}
}

void Component::moveActorZ(float z)
{
	if (mActor != nullptr)
	{
		mActor->moveZ(z);
	}
	else
	{
		getWorld().getLog() << "Invalid actor";
	}
}

World& Component::getWorld() const
{
	return World::instance();
}

} // namespace ke