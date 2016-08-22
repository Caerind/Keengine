#ifndef KE_TIME_HPP
#define KE_TIME_HPP

#include <ctime>
#include <functional>
#include <memory>
#include <string>

#include <SFML/System/Time.hpp>

#include "../Config.hpp"

namespace ke
{

std::string getTime(std::string const& timeFormat = "[%x][%X]");
double getTimeAsSeconds();
int getHours();
int getMinutes();
int getSeconds();
int getDay();
int getMonth();
int getYear();

class Timer
{
    public:
        Timer();
        ~Timer();

        typedef std::shared_ptr<Timer> Ptr;
        typedef std::function<void()> Callback;

        void setCallback(Callback callback);

        sf::Time getRemaining() const;
        sf::Time getElapsedTime() const;
        sf::Time getDuration() const;

        void setRepeat(bool repeat);
        bool isRepeated() const;

        bool isRunning() const;

        void update(sf::Time dt);

        void play();
        void pause();
        void reset(sf::Time duration);
        void stop();

    protected:
        Callback mCallback;

        bool mRunning;
        bool mRepeat;

        sf::Time mRemaining;
        sf::Time mElapsed;
        sf::Time mDuration;
};

} // namespace ke

#endif // KE_TIME_HPP
