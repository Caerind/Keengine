#include "Input.hpp"
#include "InputSystem.hpp"

Input::Input(InputSystem& system)
: mSystem(system)
{
    mSystem.addInput(this);
}

Input::~Input()
{
    mSystem.removeInput(this);
}

void Input::bindEvent(std::string const& key, std::function<void(sf::Event const& event)> func)
{
    mEvents[key] = func;
}

void Input::bindAction(std::string const& key, std::function<void()> func)
{
    mActions[key] = func;
}

void Input::unbindEvent(std::string const& key)
{
    auto itr = mEvents.find(key);
    if (itr != mEvents.end())
    {
        mEvents.erase(itr);
    }
}

void Input::unbindAction(std::string const& key)
{
    auto itr = mActions.find(key);
    if (itr != mActions.end())
    {
        mActions.erase(itr);
    }
}

bool Input::hasEvent(std::string const& key) const
{
    return (mEvents.find(key) != mEvents.end());
}

bool Input::hasAction(std::string const& key) const
{
    return (mActions.find(key) != mActions.end());
}

bool Input::handleEvent(std::string const& key, sf::Event const& event)
{
    auto itr = mEvents.find(key);
    if (itr != mEvents.end())
    {
        if (itr->second)
        {
            itr->second(event);
            return true;
        }
    }
    return false;
}

bool Input::handleAction(std::string const& key)
{
    auto itr = mActions.find(key);
    if (itr != mActions.end())
    {
        if (itr->second)
        {
            itr->second();
            return true;
        }
    }
    return false;
}
