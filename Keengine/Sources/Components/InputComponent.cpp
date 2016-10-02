#include "InputComponent.hpp"
#include "../Core/Scene.hpp"

namespace ke
{

InputComponent::InputComponent(Actor& actor) 
	: Component(actor)
{
	mUpdatable = false;
}

void InputComponent::onRegister()
{
	getApplication().getInputs().registerInput(this);
}

void InputComponent::onUnregister()
{
	getApplication().getInputs().unregisterInput(this);
}

void InputComponent::serialize(Serializer& serializer)
{
	serializer.create(getType());
	serializer.save("id", getId());
	serializer.save("priority", getPriority());
	serializer.end();
}

bool InputComponent::deserialize(Serializer& serializer, const std::string& identifier)
{
	return false;
}

} // namespace ke