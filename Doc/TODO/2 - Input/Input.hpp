#ifndef INPUT_HPP
#define INPUT_HPP

#include <functional>
#include <map>
#include <string>
#include <SFML/Window/Event.hpp>

class InputSystem;
class Input
{
    public:
        Input(InputSystem& system);
        ~Input();

        void bindEvent(std::string const& key, std::function<void(sf::Event const& event)> func);
        void bindAction(std::string const& key, std::function<void()> func);

        void unbindEvent(std::string const& key);
        void unbindAction(std::string const& key);

        bool hasEvent(std::string const& key) const;
        bool hasAction(std::string const& key) const;

        bool handleEvent(std::string const& key, sf::Event const& event);
        bool handleAction(std::string const& key);

    private:
        InputSystem& mSystem;
        std::map<std::string,std::function<void(sf::Event const& event)>> mEvents;
        std::map<std::string,std::function<void()>> mActions;
};

#endif // INPUT_HPP
