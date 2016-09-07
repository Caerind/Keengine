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
		fDef.isSensor = true;
		// TODO : Fixture Def
		mFixture = actorBody->CreateFixture(&fDef);
		mFixture->SetUserData(this);
	}
}

} // namespace ke