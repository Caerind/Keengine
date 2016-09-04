#include "CollisionComponent.hpp"
#include "../Core/Actor.hpp"

namespace ke
{

CollisionComponent::CollisionComponent()
{
	mFixture = nullptr;
}

void CollisionComponent::onRegister()
{
	if (mActor != nullptr)
	{
		b2Body* actorBody = mActor->getBody();
		if (actorBody != nullptr)
		{
			b2FixtureDef fDef;
			// TODO : Fixture Def
			mFixture = actorBody->CreateFixture(&fDef);
			mFixture->SetUserData(this);
		}
	}
}

void CollisionComponent::onUnregister()
{
	if (mActor != nullptr)
	{
		b2Body* actorBody = mActor->getBody();
		if (actorBody != nullptr)
		{
			actorBody->DestroyFixture(mFixture);
			mFixture = nullptr;
		}
	}
}

b2Fixture* CollisionComponent::getFixture()
{
	return nullptr;
}

} // namespace ke