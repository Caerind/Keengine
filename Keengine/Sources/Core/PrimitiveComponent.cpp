#include "PrimitiveComponent.hpp"
#include "World.hpp"

namespace ke
{

PrimitiveComponent::PrimitiveComponent()
	: mVisible(true)
{
    getWorld().registerPrimitive(this);
}

PrimitiveComponent::~PrimitiveComponent()
{
    getWorld().unregisterPrimitive(this);
}

void PrimitiveComponent::setVisible(bool visible)
{
	mVisible = visible;
}

bool PrimitiveComponent::isVisible() const
{
	return mVisible;
}

void PrimitiveComponent::render(sf::RenderTarget& target)
{
}

} // namespace ke