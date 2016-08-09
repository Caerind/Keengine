#include "Time.hpp"

std::string getTime(std::string const& timeFormat)
{
    time_t rawtime;
    tm timeinfo;
    char buffer[80];
    time(&rawtime);
    localtime_s(&timeinfo, &rawtime);
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
