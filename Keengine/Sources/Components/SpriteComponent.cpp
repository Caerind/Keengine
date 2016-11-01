#include "SpriteComponent.hpp"
#include "../Core/Scene.hpp"

namespace ke
{

SpriteComponent::SpriteComponent(Actor& actor) 
	: SceneComponent(actor)
	, mTexture("")
{
}

SpriteComponent::~SpriteComponent()
{
	onUnregister();
}

bool SpriteComponent::renderable() const
{
	return true;
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

std::string SpriteComponent::getTexture() const
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

void SpriteComponent::serialize(Serializer& serializer)
{
	SceneComponent::serialize(serializer);
	serializer.save("texture", getTexture());
	serializer.save("textureRect", getTextureRect());
	serializer.save("color", getColor());
}

bool SpriteComponent::deserialize(Serializer& serializer)
{
	std::string texture;
	sf::IntRect textureRect;
	sf::Color color;
	if (SceneComponent::deserialize(serializer)
		&& serializer.load("texture", texture)
		&& serializer.load("textureRect", textureRect)
		&& serializer.load("color", color))
	{
		setTexture(texture);
		setTextureRect(textureRect);
		setColor(color);
		return true;
	}
	return false;
}

void SpriteComponent::renderCurrent(sf::RenderTarget& target, sf::RenderStates states)
{
	target.draw(mSprite, states);
}

} // namespace ke