#ifndef SGUI_CONTAINER_HPP
#define SGUI_CONTAINER_HPP

#include <vector>
#include "Widget.hpp"

namespace SGUI
{

class Container : public Widget
{
    public:
        Container();

        virtual void handleEvent(sf::Event const& event);
        virtual void update(sf::Time dt);
        virtual void render(sf::RenderTarget& target, sf::RenderStates states);

		template <typename T>
        std::shared_ptr<T> createWidget();

	private:
        std::vector<Widget::Ptr> mWidgets;
};

template <typename T>
std::shared_ptr<T> Container::createWidget()
{
	std::shared_ptr<T> w = std::make_shared<T>();
	mWidgets.push_back(w);
	return w;
}

} // namespace SGUI

#endif // SGUI_CONTAINER_HPP
