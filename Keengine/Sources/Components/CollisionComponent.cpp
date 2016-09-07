#include "CollisionComponent.hpp"
#include "../Core/Actor.hpp"

namespace ke
{

CollisionComponent::CollisionComponent(Actor& actor) : SceneComponent(actor)
{
	mFixture = nullptr;
}

void CollisionComponent::onRegister()
{
	b2Body* actorBody = mActor.getBody();
	if (actorBody != nullptr)
	{
		b2FixtureDef fDef;
		// TODO : Fixture Def
		mFixture = actorBody->CreateFixture(&fDef);
		mFixture->SetUserData(this);
	}
}

void CollisionComponent::onUnregister()
{
	b2Body* actorBody = mActor.getBody();
	if (actorBody != nullptr)
	{
		actorBody->SetUserData(nullptr);
		actorBody->DestroyFixture(mFixture);
		mFixture = nullptr;
	}
}

b2Fixture* CollisionComponent::getFixture()
{
	return nullptr;
}

} // namespace ke