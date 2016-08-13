#include "../Sources/Application/Application.hpp"

#include "../Sources/Core/World.hpp"

#include "MyActor.hpp"

#include <iostream>

#include "../Sources/ExtLibs/TGUI/TGUI.hpp"

#include "../Sources/System/ScriptManager.hpp"

int main()
{
	Application::init("Example/");

	Application::createResource<Texture>("sfml", "Example/sfml.png");
	Application::createResource<Texture>("particle", "Example/particle.png");
	Application::createResource<Theme>("css", "Example/widgets.css");

	tgui::Button::Ptr button = Application::createGui<tgui::Button>("Button", "css");
	button->setPosition(350, 50);
	button->setSize(150, 50);
	button->setText("Test");
	button->connect("pressed", [&]() { std::cout << "test" << std::endl; });

	ScriptManager script;
	script.setPath("Example/");
	// TODO : Lua Library
	script.addLibrary([](sel::State& state)
	{
		state["info"] = Application::getLog().info;
	});
	script["script.lua"]["test"]();

	World::createInstance();

	World::instance().getInputs().setKeyboardMapping("MoveUp", sf::Keyboard::Z, InputType::Hold);
	World::instance().getInputs().setKeyboardMapping("MoveLeft", sf::Keyboard::Q, InputType::Hold);
	World::instance().getInputs().setKeyboardMapping("MoveDown", sf::Keyboard::S, InputType::Hold);
	World::instance().getInputs().setKeyboardMapping("MoveRight", sf::Keyboard::D, InputType::Hold);
	World::instance().getInputs().loadFromFile("Example/inputs.cfg");

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

	World::instance().getInputs().saveToFile("Example/inputs.cfg");

	World::destroyInstance();

	Application::quit();

	return 0;
}