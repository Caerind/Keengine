#ifndef SGUI_BUTTON_HPP
#define SGUI_BUTTON_HPP

#include "Widget.hpp"
#include "Sprite.hpp"
#include "Callback.hpp"

namespace SGUI
{

class Button : public Widget, public Sprite, public Callback
{
    public:
        Button();

		enum States
		{
			Normal = 0,
			Pressed = 1,
			Disabled = 2,
		};

		sf::FloatRect getBounds() const;
		bool contains(sf::Vector2f const& pos) const;

        virtual void handleEvent(sf::Event const& event);
        virtual void update(sf::Time dt);
        virtual void render(sf::RenderTarget& target, sf::RenderStates states);

        sf::Vector2f getSize() const;
        void setSize(sf::Vector2f newSize);
        void setSize(float x, float y);

	private:
		bool mPressed;
		#ifdef N_MOBILE_PLATFORM
		unsigned int mFingerId;
		#endif
};

} // namespace SGUI

#endif // SGUI_BUTTON_HPP
