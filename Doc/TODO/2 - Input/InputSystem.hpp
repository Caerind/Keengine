#ifndef INPUTSYSTEM_HPP
#define INPUTSYSTEM_HPP

#include <map>
#include <vector>

#include "Input.hpp"
#include "InputString.hpp"

class InputSystem
{
    public:
        InputSystem();
        ~InputSystem();

        void setEventMapping(std::string const& index, sf::Event::EventType eventType);
        sf::Event::EventType getEventMapping(std::string const& index);

        void setKeyboardMapping(std::string const& index, sf::Keyboard::Key key, InputType type);
        KeyboardPair getKeyboardMapping(std::string const& index);

        void setMouseMapping(std::string const& index, sf::Mouse::Button button, InputType type);
        MousePair getMouseMapping(std::string const& index);

        void handleEvent(sf::Event const& event);

        void tick(sf::Time dt);

        void addInput(Input* input);
        void removeInput(Input* input);

        void bindEvent(std::string const& key, std::function<void(sf::Event const& event)> func);
        void bindAction(std::string const& key, std::function<void()> func);

        void unbindEvent(std::string const& key);
        void unbindAction(std::string const& key);

        bool hasEvent(std::string const& key) const;
        bool hasAction(std::string const& key) const;

    private:
        std::vector<Input*> mInputs;
        std::vector<sf::Event> mEvents;
        std::map<std::string,sf::Event::EventType> mEventMapping;
        std::map<std::string,KeyboardPair> mKeyboardMapping;
        std::map<std::string,MousePair> mMouseMapping;
};

#endif // INPUTSYSTEM_HPP
