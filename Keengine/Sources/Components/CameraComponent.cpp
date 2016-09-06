#include "CameraComponent.hpp"
#include "../Core/Scene.hpp"

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
	Scene* scene = getScene();
	if (scene != nullptr)
	{
		return &scene->getView();
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
