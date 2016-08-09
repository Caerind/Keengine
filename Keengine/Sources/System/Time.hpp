#ifndef TIME_HPP
#define TIME_HPP

#include <ctime>
#include <functional>
#include <memory>
#include <string>

std::string getTime(std::string const& timeFormat = "[%x][%X]");
double getTimeAsSeconds();
int getHours();
int getMinutes();
int getSeconds();
int getDay();
int getMonth();
int getYear();

#endif // TIME_HPP
