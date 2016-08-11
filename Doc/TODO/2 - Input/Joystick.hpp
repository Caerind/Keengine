#ifndef LP_JOYSTICK_HPP
#define LP_JOYSTICK_HPP

#include <cmath>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

namespace lp
{

class Joystick : public sf::Transformable
{
    public:
        Joystick();

        void setButtonTexture(sf::Texture& texture);
        void setButtonRect(sf::IntRect const& rect);

        void setBackgroundTexture(sf::Texture& texture);
        void setBackgroundRect(sf::IntRect const& rect);

        sf::Vector2f getDelta() const;
        bool isHeld() const;

        void setDeltaMax(float dMax);

        sf::FloatRect getBounds() const;
        bool contains(sf::Vector2f const& pos) const;

        void handleEvent(sf::Event const& event);
        void render(sf::RenderTarget& target, sf::RenderStates states);

    protected:
        sf::Sprite mButton;
        sf::Sprite mBackground;
        bool mHeld;
        unsigned int mFingerId;
        float mDeltaMax;
        bool mMouse;
};

} // namespace lp

#endif // LP_JOYSTICK_HPP
