#include "InputComponent.hpp"
#include "../Core/World.hpp"

namespace ke
{

InputComponent::InputComponent()
{
	getWorld().getInputs().registerInput(this);
}

InputComponent::~InputComponent()
{
	getWorld().getInputs().unregisterInput(this);
}

} // namespace ke