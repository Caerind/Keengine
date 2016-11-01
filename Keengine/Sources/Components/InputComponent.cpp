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
	serializer.create(getType());
	serializer.save("id", getId());
	serializer.save("priority", getPriority());
	serializer.end();
}

bool InputComponent::deserialize(Serializer& serializer)
{
	return false;
}

} // namespace ke