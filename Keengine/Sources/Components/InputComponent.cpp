#include "InputComponent.hpp"
#include "../Core/Scene.hpp"

namespace ke
{

InputComponent::InputComponent(Actor& actor) : Component(actor)
{
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