#include "Actor.hpp"

#include "Scene.hpp"
#include "../Maths/Generics.hpp"

namespace ke
{

Actor::Actor(Scene& scene)
	: mRoot(*this)
	, mComponents()
	, mMarkedForRemoval(false)
	, mId("")
	, mComponentIdCounter(1)
	, mScene(scene)
	, mType("")
	, mBody(nullptr)
{
	initializePhysic();
}

Actor::~Actor()
{
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
			if (mComponents[i]->isUpdatable())
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

void Actor::attachComponent(SceneComponent::Ptr component)
{
	mRoot.attachComponent(component.get());
}

void Actor::detachComponent(SceneComponent::Ptr component)
{
	mRoot.detachComponent(component.get());
}

std::size_t Actor::getComponentCount() const
{
	return mComponents.size();
}

Component::Ptr Actor::getComponent(std::size_t index)
{
	if (index <= 0 && index < mComponents.size())
	{
		return mComponents[index];
	}
	return nullptr;
}

Component::Ptr Actor::getComponent(std::string const& id)
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

Scene& Actor::getScene()
{
	return mScene;
}

b2Body* Actor::getBody()
{
	return mBody;
}

void Actor::initializePhysic()
{
	if (mBody == nullptr && mScene.usePhysic())
	{
		b2BodyDef bDef;
		bDef.type = b2_staticBody;
		bDef.position.Set(0, 0);
		mBody = mScene.getPhysic().createBody(&bDef);
		mBody->SetUserData(this);
	}
}

void Actor::destroyPhysic()
{
	if (mBody != nullptr)
	{
		mBody->SetUserData(nullptr);
		mScene.getPhysic().destroyBody(mBody);
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

Log& Actor::getLog()
{
	return getApplication().getLog();
}

Application& Actor::getApplication()
{
	return Application::instance();
}

void Actor::removeComponent(Component::Ptr component)
{
	std::size_t size = mComponents.size();
	for (std::size_t i = 0; i < size; i++)
	{
		if (mComponents[i] == component)
		{
			mComponents.erase(mComponents.begin() + i);
			component = nullptr;
			i--;
			size--;
			return;
		}
	}
}

} // namespace ke