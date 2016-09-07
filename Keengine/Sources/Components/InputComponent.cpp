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
	getApplication().getInputs().registerInput(this);
}

void InputComponent::onUnregister()
{
	getApplication().getInputs().unregisterInput(this);
}

} // namespace ke