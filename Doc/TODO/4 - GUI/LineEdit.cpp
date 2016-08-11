#include "LineEdit.hpp"

/*

namespace SGUI
{

////////////////////////////////////////////////////////////
LineEdit::LineEdit() : Widget(), TextBox(Textures::Count), Callback(1), mActive(false), mCharacterSize(20)
{
}

////////////////////////////////////////////////////////////
void LineEdit::setString(std::string const& string)
{
    std::string str = string;
    if(isEnabled() && isVisible() && isActive())
        str += '|';
    mText.setString(str);
}

////////////////////////////////////////////////////////////
std::string LineEdit::getString() const
{
    std::string str = mText.getString();
    size_t pos = str.find('|');
    str.erase(pos, pos+1);
    return str;
}

////////////////////////////////////////////////////////////
bool LineEdit::isActive() const
{
    return mActive;
}

////////////////////////////////////////////////////////////
void LineEdit::activate()
{
    if(!isActive())
    {
        std::string str = mText.getString();
        str.push_back('|');
        mText.setString(str);

        mActive = true;
    }
}

////////////////////////////////////////////////////////////
void LineEdit::deactivate()
{
    if(isActive())
    {
        std::string str = mText.getString();
        size_t pos = str.find('|');
        str.erase(pos, pos+1);
        mText.setString(str);

        mActive = false;
    }
}

////////////////////////////////////////////////////////////
void LineEdit::setCharacterSize(size_t size)
{
    mCharacterSize = size;
    mText.setCharacterSize(size);
}

////////////////////////////////////////////////////////////
void LineEdit::update()
{
    textAlign();
    adaptTextToBox();
    Text::update();
}

////////////////////////////////////////////////////////////
void LineEdit::handleEvent(sf::Event const& event, sf::RenderWindow& RenderWindow)
{
    if(isEnabled() && isVisible())
    {
        if(isActive())
        {
            if(Event::keyLeft(event))
               moveCursorLeft();
            if(Event::keyRight(event))
                moveCursorRight();
			if(event.type == sf::Event::TextEntered)
			{
				if(event.text.unicode == '\e')
				{
					deactivate();
				}
				else if(event.text.unicode == 13)
				{
					deactivate();
				}
				else if(event.text.unicode == '\t')
				{
					deactivate();
				}
				else if(event.text.unicode == '\b')
				{
					backspace();
				}
				else
				{
					insertCharacter((char)event.text.unicode);
				}
			}
            if(Event::mouseOut(getPosition(),sf::Vector2f(mSprite.getGlobalBounds().width,mSprite.getGlobalBounds().height),RenderWindow) && Event::clickLeft(event))
                deactivate();
            if(Event::returnKey(event) && mCallbacks[0])
                mCallbacks[0]();
        }
        else if(!isActive() && Event::mouseIn(getPosition(),sf::Vector2f(mSprite.getGlobalBounds().width,mSprite.getGlobalBounds().height),RenderWindow) && Event::clickLeft(event))
            activate();

        if(isActive())
            useTextureRect(Textures::Active);
        else
            useTextureRect(Textures::Normal);
    }
    if(!isEnabled())
        useTextureRect(Textures::Disabled);
}

////////////////////////////////////////////////////////////
void LineEdit::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(isVisible())
    {
        states.transform *= getTransform();
        target.draw(mSprite,states);
        target.draw(mText,states);
    }
}

////////////////////////////////////////////////////////////
void LineEdit::moveCursorLeft()
{
    std::string str = mText.getString();
    size_t pos = str.find('|');
    if(pos > 0)
    {
        str.erase(pos, 1);
        pos--;
        str.insert(pos, "|");
        mText.setString(str);
    }
}

////////////////////////////////////////////////////////////
void LineEdit::moveCursorRight()
{
    std::string str = mText.getString();
    size_t pos = str.find('|');
    if((pos+1) < str.size())
    {
        str.erase(pos, 1);
        pos++;
        str.insert(pos, "|");
        mText.setString(str);
    }
}

////////////////////////////////////////////////////////////
void LineEdit::insertCharacter(char c)
{
    std::string str = mText.getString();
    size_t pos = str.find('|');
    str.insert(pos, 1, c);
    mText.setString(str);
}

////////////////////////////////////////////////////////////
void LineEdit::backspace()
{
    std::string str = mText.getString();
    size_t pos = str.find('|');
    if(pos > 0)
    {
        str.erase(pos, 1);
        str.erase(pos-1, 1);
        pos--;
        str.insert(pos, "|");
        mText.setString(str);
    }
}

////////////////////////////////////////////////////////////
void LineEdit::adaptTextToBox()
{
    while(mCharacterSize > getCharacterSize() && mText.getGlobalBounds().width < mSprite.getGlobalBounds().width - 8) // - 16 correspond to  padding
    {
        mText.setCharacterSize(mText.getCharacterSize()+1);
        textAlign();
    }
    while(mText.getGlobalBounds().width > mSprite.getGlobalBounds().width + 8) // + 8 correspond to  padding
    {
        mText.setCharacterSize(mText.getCharacterSize()-1);
        textAlign();
    }
}

} // namespace SGUI

*/
