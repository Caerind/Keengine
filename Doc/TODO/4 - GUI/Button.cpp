#include "Button.hpp"

namespace SGUI
{

////////////////////////////////////////////////////////////
Button::Button() : Widget(), Sprite(), Callback()
{
	mPressed = false;
}

////////////////////////////////////////////////////////////
sf::FloatRect Button::getBounds() const
{
    sf::FloatRect r = Sprite::getBounds();
    r.left += getPosition().x;
    r.top += getPosition().y;
    return r;
}

////////////////////////////////////////////////////////////
bool Button::contains(sf::Vector2f const& pos) const
{
    return Button::getBounds().contains(pos);
}

////////////////////////////////////////////////////////////
void Button::handleEvent(sf::Event const& event)
{
    if (isEnabled() && isVisible())
    {
		#ifdef N_MOBILE_PLATFORM
		if (event.type == sf::Event::TouchBegan && Button::contains(sf::Vector2f(event.touch.x,event.touch.y)))
        #else
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && Button::contains(sf::Vector2f(event.mouseButton.x,event.mouseButton.y)))
		#endif
		{
			mPressed = true;
			#ifdef N_MOBILE_PLATFORM
			mFingerId = event.touch.finger;
			#endif
		}

		if (mPressed)
		{
			#ifdef N_MOBILE_PLATFORM
			if (event.type == sf::Event::TouchEnded && event.touch.finger == mFingerId)
			#else
			if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
			#endif
			{
				mPressed = false;
				#ifdef N_MOBILE_PLATFORM
                if (Button::contains(sf::Vector2f(event.touch.x,event.touch.y)))
				#else
				if (Button::contains(sf::Vector2f(event.mouseButton.x,event.mouseButton.y)))
				#endif
				{
					callback(Button::Pressed);
				}
			}
		}
    }
}

////////////////////////////////////////////////////////////
void Button::update(sf::Time dt)
{
    if (!isEnabled() && hasTextureRect(Button::Disabled))
	{
		useTextureRect(Button::Disabled);
	}
	else if (mPressed && hasTextureRect(Button::Pressed))
	{
		useTextureRect(Button::Pressed);
	}
	else
	{
		useTextureRect(Button::Normal);
	}
}

////////////////////////////////////////////////////////////
void Button::render(sf::RenderTarget& target, sf::RenderStates states)
{
    if (isVisible())
    {
        states.transform *= getTransform();
		Sprite::render(target,states);
    }
}

////////////////////////////////////////////////////////////
sf::Vector2f Button::getSize() const
{
    return Sprite::getSize();
}

////////////////////////////////////////////////////////////
void Button::setSize(sf::Vector2f newSize)
{
    Sprite::setSize(newSize);
}

////////////////////////////////////////////////////////////
void Button::setSize(float x, float y)
{
    Sprite::setSize(x,y);
}


} // namespace SGUI

