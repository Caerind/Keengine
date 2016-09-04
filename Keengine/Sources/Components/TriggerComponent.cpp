#include "TriggerComponent.hpp"
#include "../Core/Actor.hpp"

namespace ke
{

TriggerComponent::TriggerComponent()
{
}

void TriggerComponent::onRegister()
{
	if (mActor != nullptr)
	{
		b2Body* actorBody = mActor->getBody();
		if (actorBody != nullptr)
		{
			b2FixtureDef fDef;
			fDef.isSensor = true;
			// TODO : Fixture Def
			mFixture = actorBody->CreateFixture(&fDef);
			mFixture->SetUserData(this);
		}
	}
}

} // namespace ke