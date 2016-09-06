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

} // namespace ke

#endif // KE_TIME_HPP
