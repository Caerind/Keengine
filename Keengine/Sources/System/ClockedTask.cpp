#include "ClockedTask.hpp"

ClockedTask::ClockedTask(std::function<void()> function)
: mFunction(function)
{
}

void ClockedTask::setTask(std::function<void()> function)
{
    mFunction = function;
}

sf::Time ClockedTask::execute()
{
    if (mFunction)
    {
        sf::Clock c;
        mFunction();
        return c.getElapsedTime();
    }
    else
    {
        return sf::Time::Zero;
    }
}
