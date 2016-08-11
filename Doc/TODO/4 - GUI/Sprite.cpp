#include "Sprite.hpp"

namespace SGUI
{

////////////////////////////////////////////////////////////
Sprite::Sprite()
{
}

////////////////////////////////////////////////////////////
void Sprite::setTexture(sf::Texture& texture)
{
    mSprite.setTexture(texture);
}

////////////////////////////////////////////////////////////
void Sprite::setTextureRect(int type, sf::IntRect textureRect)
{
    mRects[type] = textureRect;
}

////////////////////////////////////////////////////////////
void Sprite::useTextureRect(int type)
{
    if (hasTextureRect(type))
	{
		mSprite.setTextureRect(mRects[type]);
	}
}

////////////////////////////////////////////////////////////
bool Sprite::hasTextureRect(int type)
{
	return (mRects.find(type) != mRects.end());
}

////////////////////////////////////////////////////////////
sf::Vector2f Sprite::getSize() const
{
    return sf::Vector2f(mSprite.getGlobalBounds().width, mSprite.getGlobalBounds().height);
}

////////////////////////////////////////////////////////////
void Sprite::setSize(sf::Vector2f newSize)
{
    mSprite.setScale(mSprite.getScale().x * newSize.x / getSize().x, mSprite.getScale().y * newSize.y / getSize().y);
}

////////////////////////////////////////////////////////////
void Sprite::setSize(float x, float y)
{
    setSize(sf::Vector2f(x,y));
}

////////////////////////////////////////////////////////////
sf::FloatRect Sprite::getBounds() const
{
	return mSprite.getGlobalBounds();
}

////////////////////////////////////////////////////////////
bool Sprite::contains(sf::Vector2f const& pos) const
{
	return getBounds().contains(pos);
}

////////////////////////////////////////////////////////////
void Sprite::render(sf::RenderTarget& target, sf::RenderStates states)
{
    target.draw(mSprite,states);
}

} // namespace SGUI

