#include "SpriteComponent.hpp"
#include "../Core/Scene.hpp"

namespace ke
{

SpriteComponent::SpriteComponent(Actor& actor) 
	: SceneComponent(actor)
	, mTexture("")
{
}

void SpriteComponent::setTexture(std::string const& textureName, sf::IntRect const& rect)
{
	if (getApplication().hasResource(textureName))
	{
		if (getApplication().isResourceLoaded(textureName))
		{
			mTexture = textureName;
			setTexture(getApplication().getResource<Texture>(textureName), rect);
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