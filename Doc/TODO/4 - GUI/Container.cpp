#include "Container.hpp"

namespace SGUI
{

////////////////////////////////////////////////////////////
Container::Container()
{
}

////////////////////////////////////////////////////////////
void Container::handleEvent(sf::Event const& event)
{
    if (isEnabled() && isVisible())
	{
		std::size_t s = mWidgets.size();
		for (std::size_t i = 0; i < s; i++)
		{
			mWidgets[i]->handleEvent(event);
		}
	}
}

////////////////////////////////////////////////////////////
void Container::update(sf::Time dt)
{
    if (isEnabled() && isVisible())
	{
        std::size_t s = mWidgets.size();
		for (std::size_t i = 0; i < s; i++)
		{
			mWidgets[i]->update(dt);
		}
	}
}

////////////////////////////////////////////////////////////
void Container::render(sf::RenderTarget& target, sf::RenderStates states)
{
    if (isVisible())
	{
		states.transform *= getTransform();

		std::size_t s = mWidgets.size();
		for (std::size_t i = 0; i < s; i++)
		{
			mWidgets[i]->render(target,states);
		}
	}
}

} // namespace SGUI

