#ifndef INPUTSTRING_HPP
#define INPUTSTRING_HPP

#include <sstream>

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

enum InputType { Pressed, Released, Hold };

struct KeyboardPair
{
    KeyboardPair() {}
    KeyboardPair(sf::Keyboard::Key k, InputType t) : key(k), type(t) {}

    sf::Keyboard::Key key;
    InputType type;

    std::string toString();
    void fromString(std::string const& str);
};

struct MousePair
{
    MousePair() {}
    MousePair(sf::Mouse::Button b, InputType t) : button(b), type(t) {}

    sf::Mouse::Button button;
    InputType type;

    std::string toString();
    void fromString(std::string const& str);
};

std::string inputTypeToString(InputType type);
InputType stringToInputType(std::string const& str);

std::string eventTypeToString(sf::Event::EventType type);
sf::Event::EventType stringToEventType(std::string const& type);

std::string keyToString(sf::Keyboard::Key const& key);
sf::Keyboard::Key stringToKey(std::string const& str);

std::string buttonToString(sf::Mouse::Button const& button);
sf::Mouse::Button stringToButton(std::string const& button);

std::string unicodeToString(sf::Uint32 unicode);

#endif // INPUTSTRING_HPP
