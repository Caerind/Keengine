#include "CheckBox.hpp"

namespace SGUI
{

////////////////////////////////////////////////////////////
CheckBox::CheckBox() : Widget(), Sprite(), Callback()
{
	mChecked = false;
}

////////////////////////////////////////////////////////////
bool CheckBox::isChecked() const
{
    return mChecked;
}

////////////////////////////////////////////////////////////
void CheckBox::setChecked(bool checked)
{
    mChecked = checked;
}

////////////////////////////////////////////////////////////
sf::FloatRect CheckBox::getBounds() const
{
    sf::FloatRect r = Sprite::getBounds();
    r.left += getPosition().x;
    r.top += getPosition().y;
    return r;
}

////////////////////////////////////////////////////////////
bool CheckBox::contains(sf::Vector2f const& pos) const
{
    return CheckBox::getBounds().contains(pos);
}

////////////////////////////////////////////////////////////
void CheckBox::handleEvent(sf::Event const& event)
{
    if (isEnabled() && isVisible())
    {
		#ifdef N_MOBILE_PLATFORM
		if (event.type == sf::Event::TouchEnded && CheckBox::contains(sf::Vector2f(event.touch.x,event.touch.y)))
		#else
		if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && CheckBox::contains(sf::Vector2f(event.mouseButton.x,event.mouseButton.y)))
		#endif
		{
			mChecked = !mChecked;
			if (mChecked)
			{
				callback(CheckBox::Checked);
			}
			else
			{
				callback(CheckBox::Normal);
			}
		}
    }
}

////////////////////////////////////////////////////////////
void CheckBox::update(sf::Time dt)
{
	if (!isEnabled())
	{
		useTextureRect(CheckBox::Disabled);
	}
	else if (mChecked)
	{
		useTextureRect(CheckBox::Checked);
	}
	else
	{
		useTextureRect(CheckBox::Normal);
	}
}

////////////////////////////////////////////////////////////
void CheckBox::render(sf::RenderTarget& target, sf::RenderStates states)
{
    if (isVisible())
    {
        states.transform *= getTransform();
        Sprite::render(target,states);
    }
}

} // namespace SGUI

