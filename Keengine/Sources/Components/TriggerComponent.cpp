#include "TriggerComponent.hpp"
#include "../Core/Actor.hpp"

namespace ke
{

TriggerComponent::TriggerComponent(Actor& actor)
	: CollisionComponent(actor)
{
}

void TriggerComponent::onRegister()
{
	b2Body* actorBody = mActor.getBody();
	if (actorBody != nullptr)
	{
		b2FixtureDef fDef;
		b2PolygonShape shape;
		fDef.shape = &shape;
		fDef.isSensor = true;
		mFixture = actorBody->CreateFixture(&fDef);
		mFixture->SetUserData(this);
	}
}

} // namespace ke