#include "../Sources/Application/Application.hpp"

#include "../Sources/Core/World.hpp"

#include "MyActor.hpp"

#include <iostream>

int main()
{
	Application::init("Example/");

	Application::createResource<Texture>("sfml", "Example/sfml.png");

	World::createInstance();

	World::instance().createActor<MyActor>();

	Application::setEventDefaultFunction([&](sf::Event const& event)
	{
		World::instance().handleEvent(event);
	});

	Application::setUpdateDefaultFunction([&](sf::Time dt)
	{
		World::instance().update(dt);
	});

	Application::setRenderDefaultFunction([&](sf::RenderTarget& target)
	{
		World::instance().render(target);
	});

	Application::runDefault();

	World::destroyInstance();

	Application::quit();

	return 0;
}