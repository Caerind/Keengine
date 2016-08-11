#include "InputSystem.hpp"

InputSystem::InputSystem()
{
    addInput(new Input(*this));
}

InputSystem::~InputSystem()
{
    delete mInputs[0];
    mInputs.clear();
}

void InputSystem::setEventMapping(std::string const& index, sf::Event::EventType eventType)
{
    mEventMapping[index] = eventType;
}

sf::Event::EventType InputSystem::getEventMapping(std::string const& index)
{
    return mEventMapping[index];
}

void InputSystem::setKeyboardMapping(std::string const& index, sf::Keyboard::Key key, InputType type)
{
    mKeyboardMapping[index] = KeyboardPair(key,type);
}

KeyboardPair InputSystem::getKeyboardMapping(std::string const& index)
{
    return mKeyboardMapping[index];
}

void InputSystem::setMouseMapping(std::string const& index, sf::Mouse::Button button, InputType type)
{
    mMouseMapping[index] = MousePair(button,type);
}

MousePair InputSystem::getMouseMapping(std::string const& index)
{
    return mMouseMapping[index];
}

void InputSystem::handleEvent(sf::Event const& event)
{
    mEvents.push_back(event);
}

void InputSystem::tick(sf::Time dt)
{
    for (std::size_t i = 0; i < mEvents.size(); i++)
    {
        for (auto itr = mEventMapping.begin(); itr != mEventMapping.end(); itr++)
        {
            if (itr->second == mEvents[i].type)
            {
                bool handled = false;
                for (std::size_t j = 0; j < mInputs.size(); j++)
                {
                    if (!handled && mInputs[j]->handleEvent(itr->first,mEvents[i]))
                    {
                        handled = true;
                    }
                }
            }
        }
        if (mEvents[i].type == sf::Event::KeyPressed || mEvents[i].type == sf::Event::KeyReleased)
        {
            for (auto itr = mKeyboardMapping.begin(); itr != mKeyboardMapping.end(); itr++)
            {
                if (itr->second.type != InputType::Hold)
                {
                    bool type = false;
                    if ((itr->second.type == InputType::Pressed && mEvents[i].type == sf::Event::KeyPressed)
                     || (itr->second.type == InputType::Released && mEvents[i].type == sf::Event::KeyReleased))
                    {
                        type = true;
                    }
                    if (mEvents[i].key.code == itr->second.key && type)
                    {
                        bool handled = false;
                        for (std::size_t j = 0; j < mInputs.size(); j++)
                        {
                            if (!handled && mInputs[j]->handleAction(itr->first))
                            {
                                handled = true;
                            }
                        }
                    }
                }
            }
        }
        if (mEvents[i].type == sf::Event::MouseButtonPressed || mEvents[i].type == sf::Event::MouseButtonReleased)
        {
            for (auto itr = mMouseMapping.begin(); itr != mMouseMapping.end(); itr++)
            {
                if (itr->second.type != InputType::Hold)
                {
                    bool type = false;
                    if ((itr->second.type == InputType::Pressed && mEvents[i].type == sf::Event::MouseButtonPressed)
                     || (itr->second.type == InputType::Released && mEvents[i].type == sf::Event::MouseButtonReleased))
                    {
                        type = true;
                    }
                    if (mEvents[i].mouseButton.button == itr->second.button && type)
                    {
                        bool handled = false;
                        for (std::size_t j = 0; j < mInputs.size(); j++)
                        {
                            if (!handled && mInputs[j]->handleAction(itr->first))
                            {
                                handled = true;
                            }
                        }
                    }
                }
            }
        }
    }
    mEvents.clear();

    for (auto itr = mKeyboardMapping.begin(); itr != mKeyboardMapping.end(); itr++)
    {
        if (sf::Keyboard::isKeyPressed(itr->second.key) && itr->second.type == InputType::Hold)
        {
            bool handled = false;
            for (std::size_t j = 0; j < mInputs.size(); j++)
            {
                if (!handled && mInputs[j]->handleAction(itr->first))
                {
                    handled = true;
                }
            }
        }
    }

    for (auto itr = mMouseMapping.begin(); itr != mMouseMapping.end(); itr++)
    {
        if (sf::Mouse::isButtonPressed(itr->second.button) && itr->second.type == InputType::Hold)
        {
            bool handled = false;
            for (std::size_t j = 0; j < mInputs.size(); j++)
            {
                if (!handled && mInputs[j]->handleAction(itr->first))
                {
                    handled = true;
                }
            }
        }
    }
}

void InputSystem::addInput(Input* input)
{
    mInputs.push_back(input);
}

void InputSystem::removeInput(Input* input)
{
    for (std::size_t i = 0; i < mInputs.size();)
    {
        if (mInputs[i] == input)
        {
            mInputs.erase(mInputs.begin() + i);
        }
        else
        {
            i++;
        }
    }
}

void InputSystem::bindEvent(std::string const& key, std::function<void(sf::Event const& event)> func)
{
    mInputs[0]->bindEvent(key,func);
}

void InputSystem::bindAction(std::string const& key, std::function<void()> func)
{
    mInputs[0]->bindAction(key,func);
}

void InputSystem::unbindEvent(std::string const& key)
{
    mInputs[0]->unbindEvent(key);
}

void InputSystem::unbindAction(std::string const& key)
{
    mInputs[0]->unbindAction(key);
}

bool InputSystem::hasEvent(std::string const& key) const
{
    return mInputs[0]->hasEvent(key);
}

bool InputSystem::hasAction(std::string const& key) const
{
    return mInputs[0]->hasAction(key);
}
