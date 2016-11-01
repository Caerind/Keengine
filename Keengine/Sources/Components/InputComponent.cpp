#include "InputComponent.hpp"
#include "../Core/Scene.hpp"

namespace ke
{

InputComponent::InputComponent(Actor& actor) 
	: Component(actor)
{
}

InputComponent::~InputComponent()
{
	onUnregister();
}

void InputComponent::onRegister()
{
	if (!isRegistered())
	{
		getApplication().getInputs().registerInput(this);
		Component::onRegister();
	}
}

void InputComponent::onUnregister()
{
	if (isRegistered())
	{
		getApplication().getInputs().unregisterInput(this);
		Component::onUnregister();
	}
}

void InputComponent::serialize(Serializer& serializer)
{
	Component::serialize(serializer);
	serializer.save("priority", getPriority());
}

bool InputComponent::deserialize(Serializer& serializer)
{
	float priority;
	if (Component::deserialize(serializer) && serializer.load("priority", priority))
	{
		setPriority(priority);
		return true;
	}
	return false;
}

} // namespace ke