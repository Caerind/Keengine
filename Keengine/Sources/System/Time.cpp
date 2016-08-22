#include "Time.hpp"

namespace ke
{

std::string getTime(std::string const& timeFormat)
{
    time_t rawtime;
    tm timeinfo;
    char buffer[80];
    time(&rawtime);
	#ifndef ANDROID
    localtime_s(&timeinfo, &rawtime);
	#else
	localtime(&rawtime);
	#endif
    strftime(buffer, 80, timeFormat.c_str(), &timeinfo);
    return std::string(buffer);
}

double getTimeAsSeconds()
{
    time_t timer;
    struct tm t = {0};
    float seconds;

    t.tm_hour = 0;   t.tm_min = 0; t.tm_sec = 0;
    t.tm_year = 116; t.tm_mon = 6; t.tm_mday = 1; // 1/07/2016

    time(&timer);

    seconds = static_cast<float>(difftime(timer,mktime(&t)));

    return seconds;
}

int getHours()
{
    return std::stoi(getTime("%H"));
}

int getMinutes()
{
    return std::stoi(getTime("%M"));
}

int getSeconds()
{
    return std::stoi(getTime("%S"));
}

int getDay()
{
    return std::stoi(getTime("%d"));
}

int getMonth()
{
    return std::stoi(getTime("%m"));
}

int getYear()
{
    return std::stoi(getTime("%y"));
}

Timer::Timer()
{
    mDuration = sf::Time::Zero;
    mRemaining = sf::Time::Zero;
    mElapsed = sf::Time::Zero;
    mRunning = false;
    mRepeat = false;
}

Timer::~Timer()
{
}

void Timer::setCallback(Timer::Callback callback)
{
    mCallback = callback;
}

sf::Time Timer::getRemaining() const
{
    return mRemaining;
}

sf::Time Timer::getElapsedTime() const
{
    return mElapsed;
}

sf::Time Timer::getDuration() const
{
    return mDuration;
}

void Timer::setRepeat(bool repeat)
{
    mRepeat = repeat;
}

bool Timer::isRepeated() const
{
    return mRepeat;
}

bool Timer::isRunning() const
{
    return mRunning;
}

void Timer::update(sf::Time dt)
{
    if (mRunning)
    {
        mElapsed += dt;

        if (mDuration != sf::Time::Zero)
        {
            mRemaining -= dt;
            if (mRemaining <= sf::Time::Zero)
            {
                if (mCallback)
                {
                    mCallback();
                }

                if (mRepeat)
                {
                    reset(mDuration);
                }
                else
                {
                    stop();
                }
            }
        }
    }
}

void Timer::play()
{
    mRunning = true;
}

void Timer::pause()
{
    mRunning = false;
}

void Timer::reset(sf::Time duration)
{
    mDuration = duration;
    mRemaining = duration;
    mElapsed = sf::Time::Zero;
    mRunning = true;
}

void Timer::stop()
{
    mRunning = false;
    mRemaining = sf::Time::Zero;
    mDuration = sf::Time::Zero;
    mElapsed = sf::Time::Zero;
}

} // namespace ke