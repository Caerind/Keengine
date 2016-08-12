#include "../Sources/Application/Application.hpp"

#include "../Sources/Core/World.hpp"

#include "MyActor.hpp"

#include <iostream>

int main()
{
	Application::init("Example/");

	Application::createResource<Texture>("sfml", "Example/sfml.png");
	Application::createResource<Texture>("particle", "Example/particle.png");

	World::createInstance();
	World::instance().getView().setCenter(sf::Vector2f(0.f, 0.f));

	World::instance().getInputs().setKeyboardMapping("MoveUp", sf::Keyboard::Z, InputType::Hold);
	World::instance().getInputs().setKeyboardMapping("MoveLeft", sf::Keyboard::Q, InputType::Hold);
	World::instance().getInputs().setKeyboardMapping("MoveDown", sf::Keyboard::S, InputType::Hold);
	World::instance().getInputs().setKeyboardMapping("MoveRight", sf::Keyboard::D, InputType::Hold);

	World::instance().createActor<MyActor>()->setPosition(sf::Vector2f(100.f, 100.f));

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