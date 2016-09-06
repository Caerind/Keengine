#include "CameraComponent.hpp"
#include "../Core/World.hpp"

namespace ke
{

CameraComponent::CameraComponent() : SceneComponent()
{
}

CameraComponent::~CameraComponent()
{
}

sf::View* CameraComponent::getView()
{
	World* world = getWorld();
	if (world != nullptr)
	{
		return world->getView();
	}
	return nullptr;
}

void CameraComponent::onTransformUpdated()
{
	sf::View* view = getView();
	if (view != nullptr)
	{
		view->setCenter(getWorldPosition());
		view->setRotation(getRotation());
	}
}

} // namespace ke
