#include "CollisionComponent.hpp"
#include "../Core/Actor.hpp"
#include "../Core/PhysicSystem.hpp"

namespace ke
{

CollisionComponent::CollisionComponent(Actor& actor) 
	: SceneComponent(actor)
	, mFixture(nullptr)
{
	mUpdatable = false;
}

void CollisionComponent::onRegister()
{
	b2Body* actorBody = mActor.getBody();
	if (actorBody != nullptr && mFixture == nullptr)
	{
		b2FixtureDef fDef;
		b2PolygonShape shape;
		fDef.shape = &shape;
		mFixture = actorBody->CreateFixture(&fDef);
		mFixture->SetUserData(this);
	}
}

void CollisionComponent::onUnregister()
{
	b2Body* actorBody = mActor.getBody();
	if (actorBody != nullptr && mFixture != nullptr)
	{
		actorBody->SetUserData(nullptr);
		actorBody->DestroyFixture(mFixture);
		mFixture = nullptr;
	}
}

b2Fixture* CollisionComponent::getFixture()
{
	return mFixture;
}

b2Shape* CollisionComponent::getShape()
{
	if (mFixture != nullptr)
	{
		return mFixture->GetShape();
	}
	return nullptr;
}

b2PolygonShape* CollisionComponent::getPolygonShape()
{
	if (mFixture != nullptr)
	{
		return dynamic_cast<b2PolygonShape*>(mFixture->GetShape());
	}
	return nullptr;
}

void CollisionComponent::setDensity(float density)
{
	if (mFixture != nullptr)
	{
		mFixture->SetDensity(density);
	}
}

float CollisionComponent::getDensity()
{
	if (mFixture != nullptr)
	{
		return mFixture->GetDensity();
	}
	return 0.0f;
}

void CollisionComponent::setShape(std::vector<sf::Vector2f> shape)
{
	b2PolygonShape* polygon = getPolygonShape();
	if (polygon != nullptr)
	{
		b2Vec2 vertices[8];
		for (std::size_t i = 0; i < shape.size(); i++)
		{
			vertices[i] = shape[i] * ke::Physic::conv;
		}
		polygon->Set(vertices, shape.size());
	}
}

void CollisionComponent::serialize(Serializer& serializer)
{
	serializer.create(getType());
	serializer.save("id", getId());
	// TODO : Save data
	serializer.end();
}

bool CollisionComponent::deserialize(Serializer & serializer, const std::string & identifier)
{
	return false;
}

} // namespace ke