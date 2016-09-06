#include "Component.hpp"

#include "Actor.hpp"
#include "Scene.hpp"

namespace ke
{

Component::Component()
	: mRegistered(false)
	, mId("")
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
	return sf::Vector2f();
}

void Component::setActorPosition(sf::Vector2f const& position)
{
	if (mActor != nullptr)
	{
		mActor->setPosition(position);
	}
}

void Component::setActorPosition(float x, float y)
{
	setActorPosition(sf::Vector2f(x, y));
}

void Component::moveActor(sf::Vector2f const& movement)
{
	if (mActor != nullptr)
	{
		mActor->move(movement);
	}
}

void Component::moveActor(float x, float y)
{
	moveActor(sf::Vector2f(x, y));
}

float Component::getActorRotation() const
{
	if (mActor != nullptr)
	{
		return mActor->getRotation();
	}
	return 0.f;
}

void Component::setActorRotation(float rotation)
{
	if (mActor != nullptr)
	{
		mActor->setRotation(rotation);
	}
}

void Component::rotateActor(float rotation)
{
	if (mActor != nullptr)
	{
		mActor->rotate(rotation);
	}
}

sf::Vector2f Component::getActorScale() const
{
	if (mActor != nullptr)
	{
		return mActor->getScale();
	}
	return sf::Vector2f();
}

void Component::setActorScale(sf::Vector2f const& scale)
{
	if (mActor != nullptr)
	{
		mActor->setScale(scale);
	}
}

void Component::setActorScale(float x, float y)
{
	setActorScale(sf::Vector2f(x, y));
}

void Component::scaleActor(sf::Vector2f const& scale)
{
	if (mActor != nullptr)
	{
		mActor->scale(scale);
	}
}

void Component::scaleActor(float x, float y)
{
	scaleActor(sf::Vector2f(x, y));
}

float Component::getActorZ() const
{
	if (mActor != nullptr)
	{
		return mActor->getZ();
	}
	return 0.f;
}

void Component::setActorZ(float z)
{
	if (mActor != nullptr)
	{
		mActor->setZ(z);
	}
}

void Component::moveActorZ(float z)
{
	if (mActor != nullptr)
	{
		mActor->moveZ(z);
	}
}

std::string Component::getId() const
{
	return mId;
}

void Component::setId(std::string const& id)
{
	mId = id;
}

Actor* Component::getActor()
{
	return mActor;
}

Scene* Component::getScene()
{
	return (mActor != nullptr) ? &mActor->getScene() : nullptr;
}

Log& Component::getLog()
{
	return getApplication().getLog();
}

Application& Component::getApplication()
{
	return Application::instance();
}

} // namespace ke