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

void TriggerComponent::serialize(Serializer & serializer)
{
	serializer.create(getType());
	serializer.save("id", getId());
	// TODO : Save data
	serializer.end();
}

bool TriggerComponent::deserialize(Serializer & serializer, const std::string & identifier)
{
	return false;
}

} // namespace ke