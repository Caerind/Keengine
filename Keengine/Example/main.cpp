#include "../Sources/Application/Application.hpp"

#include "../Sources/Core/World.hpp"

#include "MyActor.hpp"
#include "MyMap.hpp"

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

	tgui::Button::Ptr button = Application::getResource<Theme>("css").create("Button");
	button->setPosition(350, 50);
	button->setSize(150, 50);
	button->setText("Hello");
	button->connect("pressed", []() { Application::getLog() << Application::inLang("hello"); Application::close(); });
	Application::getGui().add(button);

	World::createInstance();

	World::instance().getInputs().setKeyboardMapping("MoveRight", sf::Keyboard::D, InputType::Pressed);
	World::instance().getInputs().setKeyboardMapping("Stop", sf::Keyboard::D, InputType::Released);
	World::instance().getInputs().loadFromFile("Example/inputs.cfg");

	MyMap::Ptr map = World::instance().createActor<MyMap>();
	map->loadTmxFile("Example/map.tmx");
	auto layer = map->getLayer(0);

	{
		MyActor::Ptr actor = World::instance().createActor<MyActor>();
		actor->setZ(100.f);
		actor->setPosition({ 10.f, 100.f });
	}

	Application::setEventDefaultFunction([&](sf::Event const& event)
	{
		World::instance().handleEvent(event);
		if (event.type == sf::Event::MouseButtonPressed)
		{
			sf::Vector2f mPos = Application::getMousePositionView(World::instance().getView());
			sf::Vector2i coords = layer->worldToCoords(mPos);
			layer->setTileId(coords, 3);
		}
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