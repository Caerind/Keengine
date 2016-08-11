#include "Slider.hpp"

/*

namespace SGUI
{

////////////////////////////////////////////////////////////
Slider::Slider() : Widget(), Sprite(Textures::Count), Callback(1), mShape(), mInterval(), mValue(0), mMoving(false), mUseAxisX(true)
{
    mShape.setOutlineColor(sf::Color::Black);
    mShape.setOutlineThickness(1);
    for(size_t i = 0; i < mColors.size(); ++i)
        mColors[i] = sf::Color(0.1234,0.1234,0.1234,0.1234);
}

////////////////////////////////////////////////////////////
void Slider::setInterval(float a, float b)
{
    mInterval = sf::Vector2f(a,b);
}

////////////////////////////////////////////////////////////
void Slider::setCursorSize(sf::Vector2f cursorSize)
{
    mShape.setSize(cursorSize);
    mShape.setOrigin(cursorSize.x * 0.5, cursorSize.y * 0.5);
    mShape.setPosition(cursorSize.x * 0.5, mShape.getPosition().y);
}

////////////////////////////////////////////////////////////
void Slider::setCursorColor(size_t index, sf::Color color)
{
    if(index > mColors.size())
        return;
    if(color != sf::Color(0.123,0.123,0.123,0.123))
    {
        mColors[index] = color;
        if(index == 0)
        {
            mShape.setFillColor(color);
            for(size_t i = 1; i < mColors.size(); ++i)
                if(mColors[i] != sf::Color(0.1234,0.1234,0.1234,0.1234))
                    mColors[i] = color;
        }
    }
    else
        mShape.setFillColor(mColors[index]);
}

////////////////////////////////////////////////////////////
float Slider::getValueFloat() const
{
    return mValue;
}

////////////////////////////////////////////////////////////
int Slider::getValueInt() const
{
    return (int)ceil(mValue);
}

////////////////////////////////////////////////////////////
std::string Slider::getValueStringFloat() const
{
    std::stringstream ss;
    ss << mValue;
    return ss.str();
}

////////////////////////////////////////////////////////////
std::string Slider::getValueStringInt() const
{
    std::stringstream ss;
    ss << (int)ceil(mValue);
    return ss.str();
}

////////////////////////////////////////////////////////////
void Slider::update()
{
    mShape.setPosition(mShape.getPosition().x, mSprite.getGlobalBounds().height /2);
    mShape.setScale(mSprite.getScale());

    float factor;
    if(mUseAxisX)
    {
        float d = (mSprite.getGlobalBounds().width - mShape.getGlobalBounds().width / 2) - (mShape.getGlobalBounds().width / 2);
        factor = (mShape.getPosition().x + mShape.getGlobalBounds().width)/ d;
    }
    else // Using value on Axis Y
    {
        float d = (mSprite.getGlobalBounds().height - mShape.getGlobalBounds().height / 2) - (mShape.getGlobalBounds().height / 2);
        factor = (mShape.getPosition().y + mShape.getGlobalBounds().height) / d;
    }
    mValue = (mInterval.y - mInterval.x) * factor;
    mValue = std::min(mValue,mInterval.y);
    mValue = std::max(mValue,mInterval.x);
    if(mCallbacks[0])
        mCallbacks[0]();
}

////////////////////////////////////////////////////////////
void Slider::handleEvent(sf::Event const& event, sf::RenderWindow& RenderWindow)
{
    if(isVisible() && isEnabled())
    {
        if(Event::mouseIn(getPosition(),sf::Vector2f(mSprite.getGlobalBounds().width,mSprite.getGlobalBounds().height),RenderWindow))
        {
            useTextureRect(Textures::Active);
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                setCursorColor(Textures::Active);
                sf::Vector2f newPos = mShape.getPosition();
                if(mUseAxisX)
                {
                    newPos.x = static_cast<float>(sf::Mouse::getPosition(RenderWindow).x) - getPosition().x;
                    newPos.x = std::max(newPos.x,mShape.getGlobalBounds().width / 2);
                    newPos.x = std::min(newPos.x,mSprite.getGlobalBounds().width - mShape.getGlobalBounds().width / 2);
                }
                else
                {
                    newPos.y = static_cast<float>(sf::Mouse::getPosition(RenderWindow).y) - getPosition().y;
                    newPos.y = std::max(newPos.y+1,mShape.getGlobalBounds().height / 2);
                    newPos.y = std::min(newPos.y-2,mSprite.getGlobalBounds().height - mShape.getGlobalBounds().height / 2);
                }
                mShape.setPosition(newPos);
            }
            else
                setCursorColor(Textures::Normal);
        }
        else
        {
            useTextureRect(Textures::Normal);
            setCursorColor(Textures::Normal);
        }
    }
    else
    {
        useTextureRect(Textures::Disabled);
        setCursorColor(Textures::Disabled);
    }
}

////////////////////////////////////////////////////////////
void Slider::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(isVisible())
    {
        states.transform *= getTransform();
        target.draw(mSprite, states);
        target.draw(mShape, states);
    }
}


} // namespace SGUI

*/

