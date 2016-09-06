#include "InputComponent.hpp"
#include "../Core/World.hpp"

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
	World* world = getWorld();
	if (world != nullptr)
	{
		world->getInputs().registerInput(this);
	}
}

void InputComponent::onUnregister()
{
	World* world = getWorld();
	if (world != nullptr)
	{
		world->getInputs().unregisterInput(this);
	}
}

} // namespace ke