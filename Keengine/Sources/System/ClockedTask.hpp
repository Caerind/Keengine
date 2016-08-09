#ifndef CLOCKEDTASK_HPP
#define CLOCKEDTASK_HPP

#include <functional>
#include <SFML/System/Clock.hpp>

class ClockedTask
{
    public:
        ClockedTask(std::function<void()> function = [](){});

        void setTask(std::function<void()> function);

        sf::Time execute();

    protected:
        std::function<void()> mFunction;
};

#endif // CLOCKEDTASK_HPP
