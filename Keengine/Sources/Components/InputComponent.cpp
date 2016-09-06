#include "InputComponent.hpp"
#include "../Core/Scene.hpp"

namespace ke
{

InputComponent::InputComponent()
{
}

InputComponent::~InputComponent()
{
	if (isRegistered())
	{
		onUnregister();
	}
}

void InputComponent::onRegister()
{
	Scene* scene = getScene();
	if (scene != nullptr)
	{
		scene->getInputs().registerInput(this);
	}
}

void InputComponent::onUnregister()
{
	Scene* scene = getScene();
	if (scene != nullptr)
	{
		scene->getInputs().unregisterInput(this);
	}
}

} // namespace ke