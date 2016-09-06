#include "SpriteComponent.hpp"
#include "../Core/World.hpp"

namespace ke
{

SpriteComponent::SpriteComponent() : mTexture("")
{
}

void SpriteComponent::setTexture(std::string const& textureName, sf::IntRect const& rect)
{
	World* world = getWorld();
	if (world != nullptr)
	{
		if (world->hasResource(textureName))
		{
			mTexture = textureName;
			setTexture(world->getResource<Texture>(textureName), rect);
		}
	}
}

void SpriteComponent::setTexture(sf::Texture& texture, sf::IntRect const& rect)
{
    mSprite.setTexture(texture);
    if (rect != sf::IntRect())
    {
        mSprite.setTextureRect(rect);
    }
}

std::string SpriteComponent::getTextureName() const
{
	return mTexture;
}

void SpriteComponent::setTextureRect(sf::IntRect const& rect)
{
    mSprite.setTextureRect(rect);
}

sf::IntRect SpriteComponent::getTextureRect() const
{
    return mSprite.getTextureRect();
}

void SpriteComponent::setColor(sf::Color const& color)
{
    mSprite.setColor(color);
}

sf::Color SpriteComponent::getColor() const
{
    return mSprite.getColor();
}

sf::FloatRect SpriteComponent::getLocalBounds()
{
	return getTransform().transformRect(mSprite.getLocalBounds());
}

sf::FloatRect SpriteComponent::getGlobalBounds()
{
	return getWorldTransform().transformRect(mSprite.getLocalBounds());
}

void SpriteComponent::renderCurrent(sf::RenderTarget& target, sf::RenderStates states)
{
	target.draw(mSprite, states);
}

} // namespace ke