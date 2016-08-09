#include "../Sources/Application/Application.hpp"

#include "../Sources/Core/World.hpp"

#include "Blur.hpp"
#include "MyActor.hpp"
#include "Pixelate.hpp"

#include <iostream>

int main()
{
	Application::init("Example/");

	Application::createResource<Texture>("sfml", "Example/sfml.png");
	
	Shader& pixelate = Application::createResource<Shader>("pixel");
	pixelate.loadFromFile("Example/pixelate.frag", sf::Shader::Fragment);
	pixelate.setUniform("pixel_threshold", 0.005f);

	Shader& blur = Application::createResource<Shader>("blur");
	blur.loadFromFile("Example/blur.frag", sf::Shader::Fragment);
	blur.setUniform("blur_radius", 0.1f);

	World::createInstance();

	World::instance().createActor<MyActor>()->setPosition(sf::Vector2f(300.f, 300.f));

	World::instance().setEffect<Pixelate>(0);
	World::instance().setEffect<Blur>(1);

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