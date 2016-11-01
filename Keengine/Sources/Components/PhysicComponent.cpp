#include "PhysicComponent.hpp"
#include "../Core/Scene.hpp"
#include "../Core/Actor.hpp"
#include "../Core/PhysicSystem.hpp"

namespace ke
{

PhysicComponent::PhysicComponent(Actor& actor)
	: SceneComponent(actor)
	, mPoints()
	, mFixture(nullptr)
{
}

PhysicComponent::~PhysicComponent()
{
	onUnregister();
}

void PhysicComponent::onRegister()
{
	if (!isRegistered())
	{
		b2Body* actorBody = mActor.getBody();
		if (getScene().usePhysic() && actorBody != nullptr && mFixture == nullptr)
		{
			b2FixtureDef fDef;
			b2PolygonShape shape;
			fDef.shape = &shape;
			mFixture = actorBody->CreateFixture(&fDef);
			mFixture->SetUserData(this);
		}
		SceneComponent::onRegister();
	}
}

void PhysicComponent::onUnregister()
{
	if (isRegistered())
	{
		b2Body* actorBody = mActor.getBody();
		if (getScene().usePhysic() && actorBody != nullptr && mFixture != nullptr)
		{
			actorBody->SetUserData(nullptr);
			actorBody->DestroyFixture(mFixture);
			mFixture = nullptr;
		}
		SceneComponent::onUnregister();
	}
}

void PhysicComponent::setPointCount(std::size_t points)
{
	mPoints.resize(points, sf::Vector2f());
	updatePhysicShape();
}

std::size_t PhysicComponent::getPointCount() const
{
	return mPoints.size();
}

void PhysicComponent::setPoint(std::size_t index, sf::Vector2f const& point)
{
	mPoints[index] = point;
	updatePhysicShape();
}

sf::Vector2f PhysicComponent::getPoint(std::size_t index) const
{
	return mPoints[index];
}

sf::FloatRect PhysicComponent::getLocalBounds()
{
	sf::FloatRect bounds;
	if (mFixture != nullptr)
	{
		for (std::size_t i = 0; i < mPoints.size(); i++)
		{
			sf::Vector2f p = getTransform().transformPoint(mPoints[i]);
			if (i == 0)
			{
				bounds.left = p.x;
				bounds.top = p.y;
				bounds.width = p.x;
				bounds.height = p.y;
			}
			else
			{
				if (p.x < bounds.left)
				{
					bounds.left = p.x;
				}
				if (p.y < bounds.top)
				{
					bounds.top = p.y;
				}
				if (p.x > bounds.width)
				{
					bounds.width = p.x;
				}
				if (p.y > bounds.height)
				{
					bounds.height = p.y;
				}
			}
		}
		bounds.width -= bounds.left;
		bounds.height -= bounds.top;
	}
	return bounds;
}

sf::FloatRect PhysicComponent::getGlobalBounds()
{
	sf::FloatRect bounds;
	if (mFixture != nullptr)
	{
		for (std::size_t i = 0; i < mPoints.size(); i++)
		{
			sf::Vector2f p = getWorldTransform().transformPoint(mPoints[i]);
			if (i == 0)
			{
				bounds.left = p.x;
				bounds.top = p.y;
				bounds.width = p.x;
				bounds.height = p.y;
			}
			else
			{
				if (p.x < bounds.left)
				{
					bounds.left = p.x;
				}
				if (p.y < bounds.top)
				{
					bounds.top = p.y;
				}
				if (p.x > bounds.width)
				{
					bounds.width = p.x;
				}
				if (p.y > bounds.height)
				{
					bounds.height = p.y;
				}
			}
		}
		bounds.width -= bounds.left;
		bounds.height -= bounds.top;
	}
	return bounds;
}

b2Fixture* PhysicComponent::getFixture()
{
	return mFixture;
}

b2Shape* PhysicComponent::getShape()
{
	if (mFixture != nullptr)
	{
		return mFixture->GetShape();
	}
	return nullptr;
}

b2PolygonShape* PhysicComponent::getPolygonShape()
{
	if (mFixture != nullptr)
	{
		return dynamic_cast<b2PolygonShape*>(mFixture->GetShape());
	}
	return nullptr;
}

void PhysicComponent::setDensity(float density)
{
	if (mFixture != nullptr)
	{
		mFixture->SetDensity(density);
	}
}

float PhysicComponent::getDensity() const
{
	if (mFixture != nullptr)
	{
		return mFixture->GetDensity();
	}
	return 0.0f;
}

void PhysicComponent::setFriction(float friction)
{
	if (mFixture != nullptr)
	{
		mFixture->SetFriction(friction);
	}
}

float PhysicComponent::getFriction() const
{
	if (mFixture != nullptr)
	{
		return mFixture->GetFriction();
	}
	return 0.0f;
}

void PhysicComponent::setRestitution(float restitution)
{
	if (mFixture != nullptr)
	{
		mFixture->SetRestitution(restitution);
	}
}

float PhysicComponent::getRestitution() const
{
	if (mFixture != nullptr)
	{
		return mFixture->GetRestitution();
	}
	return 0.0f;
}

void PhysicComponent::setSensor(bool sensor)
{
	if (mFixture != nullptr)
	{
		mFixture->SetSensor(sensor);
	}
}

bool PhysicComponent::isSensor() const
{
	if (mFixture != nullptr)
	{
		return mFixture->IsSensor();
	}
	return false;
}

void PhysicComponent::setPoints(const std::vector<sf::Vector2f>& points)
{
	mPoints = points;
	updatePhysicShape();
}

std::vector<sf::Vector2f> PhysicComponent::getPoints() const
{
	return mPoints;
}

void PhysicComponent::serialize(Serializer& serializer)
{
	SceneComponent::serialize(serializer);
	serializer.save("points", getPoints());
	serializer.save("density", getDensity());
	serializer.save("friction", getFriction());
	serializer.save("restitution", getRestitution());
	serializer.save("sensor", isSensor());
}

bool PhysicComponent::deserialize(Serializer& serializer)
{
	std::vector<sf::Vector2f> points;
	float density;
	float friction;
	float restitution;
	bool sensor;
	if (SceneComponent::deserialize(serializer)
		&& serializer.load("points", points)
		&& serializer.load("density", density)
		&& serializer.load("friction", friction)
		&& serializer.load("restitution", restitution)
		&& serializer.load("sensor", sensor))
	{
		setPoints(points);
		setDensity(density);
		setFriction(friction);
		setRestitution(restitution);
		setSensor(sensor);
		return true;
	}
	return false;
}

void PhysicComponent::onTransformNotified()
{
	// TODO : Update Physic Shape
	// Problem is that onTransformNotified is called no matter which part change (ie even if Actor move)
	// But the Fixture position is relative to the Body (ie Actor)
	// So we need to update it ONLY if the transform of the component changes
	//updatePhysicShape();
}

void PhysicComponent::updatePhysicShape()
{
	std::size_t count = mPoints.size();
	if (mFixture != nullptr && count >= 3)
	{
		b2PolygonShape* polygon = getPolygonShape();
		if (polygon != nullptr)
		{
			b2Vec2 vertices[8];
			for (std::size_t i = 0; i < count; i++)
			{
				// TODO : Transform Points to be Actor relative
				// What if : Actor <-> NodeComponent <-> PhysicComponent ?
				vertices[i] = mPoints[i] * ke::Physic::conv;
			}
			polygon->Set(vertices, count);
		}
	}
}

} // namespace ke