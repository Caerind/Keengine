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
	serializer.create(getType());
	serializer.save("id", getId());
	serializer.save("pos", getPosition());
	serializer.save("rot", getRotation());
	serializer.save("sca", getScale());
	serializer.save("z", getZ());
	serializer.save("visible", isVisible());
	serializer.save("texture", getTexture());
	serializer.save("textureRect", getTextureRect());
	serializer.save("color", getColor());
	serializer.end();
}

bool SpriteComponent::deserialize(Serializer& serializer)
{
	return false;
}

void SpriteComponent::renderCurrent(sf::RenderTarget& target, sf::RenderStates states)
{
	target.draw(mSprite, states);
}

} // namespace ke