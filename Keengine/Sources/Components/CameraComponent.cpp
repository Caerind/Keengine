#include "CameraComponent.hpp"
#include "../Core/Scene.hpp"

namespace ke
{

CameraComponent::CameraComponent(Actor& actor) : SceneComponent(actor)
{
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

} // namespace ke
