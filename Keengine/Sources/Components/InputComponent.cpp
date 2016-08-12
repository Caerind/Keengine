#include "InputComponent.hpp"
#include "../Core/World.hpp"

InputComponent::InputComponent()
{
	getWorld().getInputs().registerInput(this);
}

InputComponent::~InputComponent()
{
	getWorld().getInputs().unregisterInput(this);
}