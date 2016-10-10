#include "Actor.hpp"

#include "Factories.hpp"
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

void Actor::initializePhysic()
{
	if (mBody == nullptr && mScene.usePhysic())
	{
		b2BodyDef bodyDef;
		bodyDef.position.Set(0, 0);
		bodyDef.type = b2_staticBody;
		bodyDef.userData = this;
		bodyDef.linearDamping = 0.01f;
		mBody = mScene.getPhysic().createBody(&bodyDef);
	}
}

void Actor::initializeComponents()
{
}

void Actor::initialize()
{
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
	if (mBody != nullptr && mBody->GetType() != b2_staticBody)
	{
		setPosition(mBody->GetPosition() * Physic::conv);
		setRotation(radToDeg(mBody->GetAngle()));
	}
}

void Actor::desiredImpulseX(float impulse)
{
	impulse = impulse / Physic::pixelsPerMeter;
	if (mBody != nullptr && mScene.usePhysic())
	{
		if (mBody->GetType() != b2_staticBody)
		{
			mBody->ApplyLinearImpulse(b2Vec2(mBody->GetMass() * (impulse - mBody->GetLinearVelocity().x), 0.f), mBody->GetWorldCenter(), true);
		}
	}
}

void Actor::desiredImpulseY(float impulse)
{
	impulse = impulse / Physic::pixelsPerMeter;
	if (mBody != nullptr && mScene.usePhysic())
	{
		if (mBody->GetType() != b2_staticBody)
		{
			mBody->ApplyLinearImpulse(b2Vec2(0.f, mBody->GetMass() * (impulse - mBody->GetLinearVelocity().y)), mBody->GetWorldCenter(), true);
		}
	}
}

void Actor::setVelocity(sf::Vector2f const& velocity)
{
	if (mBody != nullptr && mScene.usePhysic())
	{
		mBody->SetLinearVelocity(velocity * Physic::conv);
	}
}

sf::Vector2f Actor::getVelocity() const
{
	if (mBody != nullptr && mScene.usePhysic())
	{
		return mBody->GetLinearVelocity() * Physic::conv;
	}
	return sf::Vector2f();
}

void Actor::setAngularVelocity(float angularVelocity)
{
	if (mBody != nullptr)
	{
		mBody->SetAngularVelocity(angularVelocity);
	}
}

float Actor::getAngularVelocity() const
{
	if (mBody != nullptr)
	{
		return mBody->GetAngularVelocity();
	}
	return 0.0f;
}

void Actor::setPhysicType(b2BodyType const& type)
{
	if (mBody != nullptr)
	{
		mBody->SetType(type);
	}
}

b2BodyType Actor::getPhysicType() const
{
	if (mBody != nullptr)
	{
		return mBody->GetType();
	}
	return b2_staticBody;
}

void Actor::setFixedRotation(bool fixed)
{
	if (mBody != nullptr)
	{
		mBody->SetFixedRotation(fixed);
	}
}

bool Actor::isFixedRotation() const
{
	if (mBody != nullptr)
	{
		return mBody->IsFixedRotation();
	}
	return false;
}

float Actor::getMass() const
{
	if (mBody != nullptr)
	{
		return mBody->GetMass();
	}
	return 0.0f;
}

float Actor::getInertia() const
{
	if (mBody != nullptr)
	{
		return mBody->GetInertia();
	}
	return 0.0f;
}

void Actor::setLinearDamping(float damping)
{
	if (mBody != nullptr)
	{
		mBody->SetLinearDamping(damping);
	}
}

float Actor::getLinearDamping() const
{
	if (mBody != nullptr)
	{
		return mBody->GetLinearDamping();
	}
	return 0.0f;
}

void Actor::setAngularDamping(float damping)
{
	if (mBody != nullptr)
	{
		mBody->SetAngularDamping(damping);
	}
}

float Actor::getAngularDamping() const
{
	if (mBody != nullptr)
	{
		return mBody->GetAngularDamping();
	}
	return 0.0f;
}

void Actor::setGravityScale(float scale)
{
	if (mBody != nullptr)
	{
		mBody->SetGravityScale(scale);
	}
}

float Actor::getGravityScale() const
{
	if (mBody != nullptr)
	{
		return mBody->GetGravityScale();
	}
	return 0.0f;
}

void Actor::setPhysicBullet(bool bullet)
{
	if (mBody != nullptr)
	{
		mBody->SetBullet(bullet);
	}
}

bool Actor::isPhysicBullet() const
{
	if (mBody != nullptr)
	{
		return mBody->IsBullet();
	}
	return false;
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

void Actor::serialize(Serializer& serializer)
{
	serializer.create(getType());
	serializer.save("id", getId());
	// TODO : Save more data (physic, ...)
	for (std::size_t i = 0; i < mComponents.size(); i++)
	{
		mComponents[i]->serialize(serializer);
	}
	serializer.end();
}

bool Actor::deserialize(Serializer& serializer)
{
	return false;
}

} // namespace ke