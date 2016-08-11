#ifndef SGUI_CHECKBOX_HPP
#define SGUI_CHECKBOX_HPP

#include "Widget.hpp"
#include "Sprite.hpp"
#include "Callback.hpp"

namespace SGUI
{

class CheckBox : public Widget, public Sprite, public Callback
{
    public:
        CheckBox();

		enum States
        {
            Normal = 0,
			Checked = 1,
            Disabled = 2,
        };

        bool isChecked() const;
		void setChecked(bool checked);

		sf::FloatRect getBounds() const;
		bool contains(sf::Vector2f const& pos) const;

        virtual void handleEvent(sf::Event const& event);
        virtual void update(sf::Time dt);
		virtual void render(sf::RenderTarget& target, sf::RenderStates states);

    private:
        bool mChecked;
};

} // namespace SGUI

#endif // SGUI_CHECKBOX_HPP
