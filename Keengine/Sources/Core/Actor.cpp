#include "Actor.hpp"

#include "World.hpp"
#include "../Maths/Generics.hpp"

namespace ke
{

Actor::Actor()
	: mRoot()
	, mComponents()
	, mMarkedForRemoval(false)
	, mId("")
	, mComponentIdCounter(1)
	, mWorld(nullptr)
	, mType("")
	, mBody(nullptr)
{
}

Actor::~Actor()
{
	unregisterComponents();
	destroyPhysic();
}

void Actor::remove()
{
	mMarkedForRemoval = true;
}

bool Actor::isMarkedForRemoval() const
{
	return mMarkedForRemoval;
}

void Actor::setId(std::string const & id)
{
	mId = id;
}

std::string Actor::getId() const
{
	return mId;
}

std::string Actor::getType() const
{
	return mType;
}

const sf::Vector2f& Actor::getPosition() const
{
	return mRoot.getPosition();
}

void Actor::setPosition(sf::Vector2f const& position)
{
	mRoot.setPosition(position);
}

void Actor::setPosition(float x, float y)
{
	setPosition(sf::Vector2f(x, y));
}

void Actor::move(sf::Vector2f const& movement)
{
	mRoot.move(movement);
}

void Actor::move(float x, float y)
{
	move(sf::Vector2f(x, y));
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

void Actor::setScale(float x, float y)
{
	setScale(sf::Vector2f(x, y));
}

void Actor::scale(sf::Vector2f const & scale)
{
	mRoot.scale(scale);
}

void Actor::scale(float x, float y)
{
	scale(sf::Vector2f(x, y));
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

bool Actor::isVisible() const
{
	return mRoot.isVisible();
}

void Actor::setVisible(bool visible)
{
	mRoot.setVisible(visible);
}

void Actor::update(sf::Time dt)
{
}

void Actor::updateComponents(sf::Time dt)
{
	std::size_t size = mComponents.size();
	for (std::size_t i = 0; i < size; i++)
	{
		if (mComponents[i] != nullptr)
		{
			if (mComponents[i]->isUpdatable() && mComponents[i]->isRegistered())
			{
				mComponents[i]->update(dt);
			}
		}
	}
}

void Actor::render(sf::RenderTarget& target)
{
	mRoot.render(target, sf::RenderStates::Default);
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
	if (component != nullptr && std::find(mComponents.begin(), mComponents.end(), component) == mComponents.end())
	{
		component->registerComponent(this);
		component->setId(ke::decToHex(mComponentIdCounter++));
		mComponents.push_back(component);
	}
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
				return;
			}
		}
	}
}

void Actor::unregisterComponents()
{
	std::size_t size = mComponents.size();
	for (std::size_t i = 0; i < size; i++)
	{
		if (mComponents[i] != nullptr)
		{
			if (mComponents[i]->isRegistered())
			{
				mComponents[i]->onUnregister();
			}
		}
	}
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

void Actor::setWorld(World * world)
{
	mWorld = world;
}

World* Actor::getWorld()
{
	return mWorld;
}

b2Body* Actor::getBody()
{
	return mBody;
}

void Actor::initializePhysic()
{
	if (mBody == nullptr && mWorld != nullptr)
	{
		b2BodyDef bDef;
		bDef.type = b2_dynamicBody;
		bDef.position.Set(0, 0);
		mBody = mWorld->getPhysic().createBody(&bDef);
		mBody->SetUserData(this);
	}
}

void Actor::destroyPhysic()
{
	if (mBody != nullptr)
	{
		mBody->GetWorld()->DestroyBody(mBody);
		mBody = nullptr;
	}
}

void Actor::prePhysicUpdate()
{
	if (mBody != nullptr)
	{
		mBody->SetTransform(getPosition() * Physic::conv, degToRad(getRotation()));
	}
}

void Actor::postPhysicUpdate()
{
	if (mBody != nullptr)
	{
		setPosition(mBody->GetPosition() * Physic::conv);
		setRotation(radToDeg(mBody->GetAngle()));
	}
}

} // namespace ke