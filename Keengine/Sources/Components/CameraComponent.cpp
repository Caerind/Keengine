#include "CameraComponent.hpp"
#include "../Core/Scene.hpp"

namespace ke
{

CameraComponent::CameraComponent(Actor& actor) 
	: SceneComponent(actor)
{
	mUpdatable = false;
}

sf::View& CameraComponent::getView()
{
	return getScene().getView();
}

void CameraComponent::onTransformUpdated()
{
	getView().setCenter(getWorldPosition());
	getView().setRotation(getRotation());
}

void CameraComponent::serialize(Serializer& serializer)
{
	serializer.create(getType());
	serializer.save("id", getId());
	serializer.save("pos", getPosition());
	serializer.save("rot", getRotation());
	serializer.end();
}

bool CameraComponent::deserialize(Serializer& serializer)
{
	return false;
}

} // namespace ke
