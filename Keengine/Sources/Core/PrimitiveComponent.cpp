#include "PrimitiveComponent.hpp"
#include "World.hpp"

PrimitiveComponent::PrimitiveComponent()
	: mRenderable(true)
{
    getWorld().registerPrimitive(this);
}

PrimitiveComponent::~PrimitiveComponent()
{
    getWorld().unregisterPrimitive(this);
}
		
bool PrimitiveComponent::isRenderable() const
{
	return mRenderable;
}

void PrimitiveComponent::render(sf::RenderTarget& target)
{
}
