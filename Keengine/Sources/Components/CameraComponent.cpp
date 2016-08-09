#include "CameraComponent.hpp"
#include "../Core/World.hpp"

CameraComponent::CameraComponent() : SceneComponent()
{
	mCamera = getWorld().getView();
	getWorld().registerCamera(this);
}

CameraComponent::~CameraComponent()
{
	getWorld().unregisterCamera(this);
}

sf::View& CameraComponent::getView()
{
	return mCamera;
}

void CameraComponent::onChangedTransform()
{
	SceneComponent::onChangedTransform();
	mCamera.setCenter(getWorldPosition());
	mCamera.setRotation(getRotation());
	// TODO : Camera Zoom
}
