#ifndef STRING_HPP
#define STRING_HPP

#include <iostream>
#include <algorithm>
#include <string>
#include <typeinfo>
#include <vector>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>



void toLower(std::string& str);
void toUpper(std::string& str);

std::string split(std::string& base, char separator);
std::string split(std::string& base, std::string const& separator);
std::vector<std::string> splitVector(std::string str, std::string const& separator);

bool contains(std::string const& str, char c);
bool contains(std::string const& str, std::string const& c);

std::string limitSize(std::string str, std::size_t size);

std::string toString(sf::FloatRect const& rect);
std::string toString(sf::IntRect const& rect);
std::string toString(sf::Color const& color);
std::string toString(sf::Vector2f const& v);
std::string toString(sf::Vector2i const& v);
sf::FloatRect toFloatRect(std::string str);
sf::IntRect toIntRect(std::string str);
sf::Color toColor(std::string str);
sf::Vector2f toVector2f(std::string str);
sf::Vector2i toVector2i(std::string str);

#endif // STRING_HPP
