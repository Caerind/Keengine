#include "Actor.hpp"

#include "World.hpp"
#include "../Maths/Generics.hpp"

Actor::Actor(std::string const& id)
	: mRoot()
	, mComponents()
	, mMarkedForRemoval(false)
	, mId()
{
	if (id == "")
	{
		std::ostringstream oss;
		oss << std::hex << getWorld().getActualId();
		mId = oss.str();
	}
	else
	{
		mId = id;
	}
}

Actor::~Actor()
{
}

void Actor::remove()
{
	mMarkedForRemoval = true;
}

bool Actor::isMarkedForRemoval() const
{
	return mMarkedForRemoval;
}

void Actor::onCreated()
{
}

void Actor::onDestroyed()
{
}

std::string Actor::getId() const
{
	return mId;
}

const sf::Vector2f& Actor::getPosition() const
{
	return mRoot.getPosition();
}

void Actor::setPosition(sf::Vector2f const& position)
{
	mRoot.setPosition(position);
}

void Actor::move(sf::Vector2f const& movement)
{
	mRoot.move(movement);
}

float Actor::getRotation() const
{
	return mRoot.getRotation();
}

void Actor::setRotation(float rotation)
{
	mRoot.setRotation(rotation);
}

void Actor::rotate(float rotation)
{
	mRoot.rotate(rotation);
}

const sf::Vector2f& Actor::getScale() const
{
	return mRoot.getScale();
}

void Actor::setScale(sf::Vector2f const & scale)
{
	mRoot.setScale(scale);
}

void Actor::scale(sf::Vector2f const & scale)
{
	mRoot.scale(scale);
}

float Actor::getZ() const
{
	return mRoot.getZ();
}

void Actor::setZ(float z)
{
	mRoot.setZ(z);
}

void Actor::moveZ(float z)
{
	mRoot.moveZ(z);
}

void Actor::update(float dt)
{
}

void Actor::updateComponents(float dt)
{
}

void Actor::attachComponent(SceneComponent* component)
{
	mRoot.attachComponent(component);
}

void Actor::detachComponent(SceneComponent* component)
{
	mRoot.detachComponent(component);
}

void Actor::registerComponent(Component* component)
{
	component->registerComponent(this);
	mComponents.push_back(component);
}

void Actor::unregisterComponent(Component* component)
{
	if (component != nullptr)
	{
		std::size_t size = mComponents.size();
		for (std::size_t i = 0; i < size; i++)
		{
			if (mComponents[i] == component)
			{
				component->unregisterComponent(this);
				mComponents.erase(i + mComponents.begin());
				size--;
			}
		}
	}
}

World& Actor::getWorld() const
{
	return World::instance();
}