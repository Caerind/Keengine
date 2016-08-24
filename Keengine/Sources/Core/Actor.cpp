#include "Actor.hpp"

#include "World.hpp"
#include "../Maths/Generics.hpp"

namespace ke
{

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

	b2BodyDef bDef;
	bDef.type = b2_dynamicBody;
	mBody = getWorld().getPhysic().createBody(&bDef);
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

void Actor::setId(std::string const & id)
{
	mId = id;
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

const sf::Transform& Actor::getTransform()
{
	return mRoot.getWorldTransform();
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

void Actor::update(sf::Time dt)
{
}

void Actor::updateComponents(sf::Time dt)
{
	std::size_t size = mComponents.size();
	for (std::size_t i = 0; i < size; i++)
	{
		mComponents[i]->update(dt);
	}
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

b2Body* Actor::getBody()
{
	return mBody;
}

std::size_t Actor::getActualId()
{
	return mIdCounter++;
}

std::size_t Actor::getComponentCount() const
{
	return mComponents.size();
}

Component* Actor::getComponent(std::size_t index)
{
	if (index <= 0 && index < mComponents.size())
	{
		return mComponents[index];
	}
	return nullptr;
}

Component* Actor::getComponent(std::string const& id)
{
	for (std::size_t i = 0; i < mComponents.size(); i++)
	{
		if (mComponents[i] != nullptr)
		{
			if (mComponents[i]->getId() == id)
			{
				return mComponents[i];
			}
		}
	}
	return nullptr;
}

} // namespace ke