#ifndef SGUI_WIDGET_HPP
#define SGUI_WIDGET_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window.hpp>
#include <memory>
#include <array>

namespace SGUI
{

class Widget : public sf::Transformable
{
    public:
        typedef std::shared_ptr<Widget> Ptr;

    public:
        Widget();

        bool isEnabled() const;
        void enable();
        void disable();

        bool isVisible() const;
        void show();
        void hide();

        virtual sf::Vector2f getSize() const;
        virtual void setSize(sf::Vector2f newSize);
        virtual void setSize(float x, float y);

        virtual void handleEvent(sf::Event const& event);
        virtual void update(sf::Time dt);
		virtual void render(sf::RenderTarget& target, sf::RenderStates states);

    protected:
        bool mEnabled;
        bool mVisible;
};

} // namespace SGUI

#endif // SGUI_WIDGET_HPP
