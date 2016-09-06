#include "../Sources/Application/Application.hpp"

#include "../Sources/Core/Scene.hpp"

#include "MyActor.hpp"
#include "MyMap.hpp"

int main()
{
	ke::Application::init("Example/");

	ke::Application::createResource<ke::Texture>("sfml", "Example/sfml.png");
	ke::Application::createResource<ke::Texture>("particle", "Example/particle.png");
	ke::Application::createResource<ke::Texture>("cat", "Example/cat.png");
	ke::Application::createResource<ke::Theme>("css", "Example/widgets.css");

	ke::Application::createResource<ke::Lang>("english", "Example/English.lang");
	ke::Application::createResource<ke::Lang>("french", "Example/French.lang");

	/*
	ke::Application::setLang("french");
	tgui::Button::Ptr button = ke::Application::getResource<ke::Theme>("css").create("Button");
	button->setPosition(350, 50);
	button->setSize(150, 50);
	button->setText(std::to_string(ke::Application::getSize().x) + " " + std::to_string(ke::Application::getSize().y));
	button->connect("pressed", []() { ke::Application::getLog() << ke::Application::inLang("hello"); ke::Application::close(); });
	ke::Application::getGui().add(button);
	*/

	ke::Application::getInputs().setKeyboardMapping("MoveRight", sf::Keyboard::D, ke::InputType::Pressed);
	ke::Application::getInputs().setKeyboardMapping("Stop", sf::Keyboard::D, ke::InputType::Released);
	ke::Application::getInputs().loadFromFile("Example/inputs.cfg");

	ke::Scene scene;

	MyMap::Ptr map = scene.createActor<MyMap>();
	map->loadTmxString("<?xml version=\"1.0\" encoding=\"UTF-8\"?>" \
		"<map version=\"1.0\" orientation=\"staggered\" renderorder=\"right-down\" width=\"10\" height=\"10\" tilewidth=\"256\" tileheight=\"128\" staggeraxis=\"y\" staggerindex=\"odd\" nextobjectid=\"1\">" \
		" <tileset firstgid=\"1\" name=\"iso\" tilewidth=\"256\" tileheight=\"128\" tilecount=\"4\" columns=\"4\">" \
		"  <image source=\"Example/iso.png\" width=\"1024\" height=\"128\"/>" \
		" </tileset>" \
		" <layer name=\"Calque de Tile 1\" width=\"10\" height=\"10\">" \
		"  <data encoding=\"base64\" compression=\"zlib\">" \
		"   eJxjYmBgYKIyZkHCxKgbrOYNBAYAtwAA4w==" \
		"  </data>" \
		" </layer>" \
		"</map>");
	auto layer = map->getLayer(0);

	MyActor::Ptr actor = scene.createActor<MyActor>();
	actor->setZ(100.f);
	actor->setPosition({ 10.f, 100.f });

	ke::Application::setEventDefaultFunction([&](sf::Event const& event)
	{
		if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::TouchBegan)
		{
			sf::Vector2f mPos = ke::Application::getPointerPositionView(scene.getView());
			sf::Vector2i coords = layer->worldToCoords(mPos);
			layer->setTileId(coords, 3);
		}
	});

	ke::Application::setUpdateDefaultFunction([&](sf::Time dt)
	{
		scene.update(dt);
		ke::Application::setDebugInfo("Actors", scene.getActorCount());
	});

	ke::Application::setRenderDefaultFunction([&](sf::RenderTarget& target)
	{
		scene.render(target);
	});

	ke::Application::runDefault();

	map = nullptr;
	layer = nullptr;
	actor = nullptr;

	ke::Application::getInputs().saveToFile("Example/inputs.cfg");

	ke::Application::quit();

	return 0;
}