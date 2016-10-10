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
	mUpdatable = false;
}

void PhysicComponent::onRegister()
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
}

void PhysicComponent::onUnregister()
{
	b2Body* actorBody = mActor.getBody();
	if (getScene().usePhysic() && actorBody != nullptr && mFixture != nullptr)
	{
		actorBody->SetUserData(nullptr);
		actorBody->DestroyFixture(mFixture);
		mFixture = nullptr;
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
	if (mFixture != nullptr)
	{
		// TODO : Rect from points
	}
	return sf::FloatRect();
}

sf::FloatRect PhysicComponent::getGlobalBounds()
{
	if (mFixture != nullptr)
	{
		// TODO : Rect from points
	}
	return sf::FloatRect();
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
	serializer.create(getType());
	serializer.save("id", getId());
	serializer.save("pos", getPosition());
	serializer.save("rot", getRotation());
	serializer.save("sca", getScale());
	serializer.save("z", getZ());
	//serializer.save("visible", isVisible());
	serializer.save("points", getPoints());
	serializer.save("density", getDensity());
	serializer.save("friction", getFriction());
	serializer.save("restitution", getRestitution());
	serializer.save("sensor", isSensor());
	serializer.end();
}

bool PhysicComponent::deserialize(Serializer& serializer)
{
	return false;
}

void PhysicComponent::onTransformUpdated()
{
	// TODO : Update Transform
	//updatePhysicShape();
}

void PhysicComponent::updatePhysicShape()
{
	if (mFixture != nullptr)
	{
		b2PolygonShape* polygon = getPolygonShape();
		if (polygon != nullptr)
		{
			b2Vec2 vertices[8];
			std::size_t count = mPoints.size();
			for (std::size_t i = 0; i < count; i++)
			{
				// TODO : Transform Points to be Actor relative
				vertices[i] = mPoints[i] * ke::Physic::conv;
			}
			polygon->Set(vertices, count);
		}
	}
}

} // namespace ke