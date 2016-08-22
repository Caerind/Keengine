#include "SpriteComponent.hpp"
#include "../Core/World.hpp"

namespace ke
{

SpriteComponent::SpriteComponent() : mTexture("")
{
}

void SpriteComponent::setTexture(std::string const& textureName, sf::IntRect const& rect)
{
	if (getWorld().getApplication().hasResource(textureName))
	{
		setTexture(getWorld().getApplication().getResource<Texture>(textureName), rect);
		mTexture = textureName;
	}
}

void SpriteComponent::setTexture(sf::Texture& texture, sf::IntRect const& rect)
{
    mSprite.setTexture(texture);
    if (rect != sf::IntRect())
    {
        setTextureRect(rect);
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

void SpriteComponent::render(sf::RenderTarget& target)
{
    target.draw(mSprite, sf::RenderStates(getWorldTransform()));
}

sf::FloatRect SpriteComponent::getLocalBounds()
{
	return getTransform().transformRect(mSprite.getLocalBounds());
}

sf::FloatRect SpriteComponent::getGlobalBounds()
{
	return getWorldTransform().transformRect(mSprite.getLocalBounds());
}

} // namespace ke