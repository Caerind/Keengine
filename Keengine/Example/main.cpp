#include "../Sources/Application/Application.hpp"

#include "../Sources/Core/World.hpp"
#include "../Sources/Core/Map.hpp"

#include "MyActor.hpp"

int main()
{
	Application::init("Example/");

	Application::createResource<Texture>("sfml", "Example/sfml.png");
	Application::createResource<Texture>("particle", "Example/particle.png");
	Application::createResource<Texture>("cat", "Example/cat.png");
	Application::createResource<Theme>("css", "Example/widgets.css");

	Application::createResource<Lang>("english", "Example/English.lang");
	Application::createResource<Lang>("french", "Example/French.lang");

	Application::setLang("french");

	tgui::Button::Ptr button = Application::createGui<tgui::Button>("Button", "css");
	button->setPosition(350, 50);
	button->setSize(150, 50);
	button->setText("Hello");
	button->connect("pressed", []() { Application::getLog() << Application::inLang("hello"); });

	World::createInstance();

	World::instance().getInputs().setKeyboardMapping("MoveRight", sf::Keyboard::D, InputType::Pressed);
	World::instance().getInputs().setKeyboardMapping("Stop", sf::Keyboard::D, InputType::Released);
	World::instance().getInputs().loadFromFile("Example/inputs.cfg");

	{
		Map::Ptr map = World::instance().createActor<Map>();
		map->loadTmxFile("Example/map.tmx");

		MyActor::Ptr actor = World::instance().createActor<MyActor>();
		actor->setZ(100.f);
		actor->setPosition({ 10.f, 100.f });
	}

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