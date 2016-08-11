#ifndef LP_KEYBINDING_HPP
#define LP_KEYBINDING_HPP

#include <map>
#include <cassert>
#include <string>
#include <fstream>
#include "Pugixml.hpp"

#include <SFML/Window/Keyboard.hpp>

namespace lp
{

std::string keyToString(sf::Keyboard::Key const& key);
sf::Keyboard::Key stringToKey(std::string const& str);

class KeyBinding
{
    public:
        KeyBinding();
        ~KeyBinding();

        void setKey(std::string const& id, sf::Keyboard::Key key);
        sf::Keyboard::Key getKey(std::string const& id);
        std::string getKeyString(std::string const& id);

        bool load(std::string const& filename);
        void save(std::string const& filename);

    protected:
        std::map<std::string,sf::Keyboard::Key> mKeys;
};

} // namespace lp

#endif // LP_KEYBINDING_HPP
