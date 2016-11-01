#include "../Sources/Application/Application.hpp"

#include "../Sources/Core/Scene.hpp"
#include "../Sources/Core/Actor.hpp"
#include "../Sources/Core/Factories.hpp"

#include "MyActor.hpp"
#include "MyMap.hpp"

#include "../Sources/Components/Components.hpp"

#include "../Sources/System/Serializer.hpp"

int main()
{
	ke::Application::init("Example/");

	ke::Application::createResource<ke::Texture>("sfml", "Example/sfml.png");
	ke::Application::createResource<ke::Texture>("particle", "Example/particle.png");
	ke::Application::createResource<ke::Texture>("cat", "Example/cat.png");
	ke::Application::createResource<ke::Theme>("css", "Example/widgets.css");

	ke::Application::createResource<ke::Lang>("english", "Example/English.lang");
	ke::Application::createResource<ke::Lang>("french", "Example/French.lang");

	ke::Application::setLang("french");

	tgui::Gui gui(ke::Application::getWindow());
	tgui::Button::Ptr button = ke::Application::getResource<ke::Theme>("css").create("Button");
	button->setPosition(350, 50);
	button->setSize(150, 50);
	button->setText(std::to_string(ke::Application::getSize().x) + " " + std::to_string(ke::Application::getSize().y));
	button->connect("pressed", []() { ke::Application::getLog() << ke::Application::inLang("hello"); });
	gui.add(button);

	ke::Application::getInputs().setKeyboardMapping("MoveUp", sf::Keyboard::Z, ke::InputType::Hold);
	ke::Application::getInputs().setKeyboardMapping("MoveLeft", sf::Keyboard::Q, ke::InputType::Hold);
	ke::Application::getInputs().setKeyboardMapping("MoveDown", sf::Keyboard::S, ke::InputType::Hold);
	ke::Application::getInputs().setKeyboardMapping("MoveRight", sf::Keyboard::D, ke::InputType::Hold);
	ke::Application::getInputs().setKeyboardMapping("Light", sf::Keyboard::L, ke::InputType::Pressed);
	ke::Application::getInputs().loadFromFile("Example/inputs.cfg");
	
	ke::Factories::registerActor<MyActor>();
	ke::Factories::registerActor<MyMap>();

	ke::Scene scene("main", ke::Scene::Light | ke::Scene::Physic);
	scene.getPhysic()->setPixelsPerMeter(32.f);
	scene.getPhysic()->setRenderDebug(true);
	scene.getPhysic()->setGravity(b2Vec2(0, 9.8f));
	scene.useBackgroundRepeatedTexture(&ke::Application::getResource<ke::Texture>("sfml"));

	MyMap::Ptr map = scene.createActor<MyMap>("map");
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
		" <objectgroup name=\"Calque d'objets 1\">" \
		"  <object id=\"4\" x=\"99\" y=\"43\" width=\"146\" height=\"48\" />" \
		"  <object id=\"5\" x=\"493\" y=\"115\" width=\"186\" height=\"62\" />" \
		"  <object id=\"6\" x=\"-41\" y=\"486\" width=\"1129\" height=\"214\" />" \
		"  <object id=\"7\" x=\"292\" y=\"465\" width=\"78\" height=\"48\" />" \
		"  <object id=\"8\" x=\"773\" y=\"381\" width=\"70\" height=\"120\" />" \
		"  <object id=\"10\" x=\"930\" y=\"256\" width=\"66\" height=\"46\" />" \
		" </objectgroup>" \
		"</map>");
	ke::LayerComponent::Ptr layer = map->getLayer(0);

	MyActor::Ptr actor = scene.createActor<MyActor>("player");
	actor->setZ(100.f);
	actor->setPosition({ 100.f, 300.f });

	ke::Texture& lightTexture = scene.getApplication().getResource<ke::Texture>("pointLightTexture");
	ke::PointLightComponent::Ptr mouseLight = scene.createComponent<ke::PointLightComponent>();
	scene.attachComponent(mouseLight);
	if (scene.useLight())
	{
		mouseLight->setTexture("pointLightTexture");
		mouseLight->setOrigin(sf::Vector2f(lightTexture.getSize().x * 0.5f, lightTexture.getSize().y * 0.5f));
		mouseLight->setPosition(ke::Application::getPointerPositionView(scene.getView()));
		mouseLight->setColor(sf::Color::White);
		mouseLight->setIntensity(3.f);
	}

	ke::Application::setEventDefaultFunction([&](sf::Event const& event)
	{
		gui.handleEvent(event);
		if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::TouchBegan)
		{
			sf::Vector2f mPos = ke::Application::getPointerPositionView(scene.getView());

			if (layer != nullptr)
			{
				sf::Vector2i coords = layer->worldToCoords(mPos);
				layer->setTileId(coords, 3);
			}

			if (scene.useLight())
			{
				ke::PointLightComponent::Ptr light = scene.createComponent<ke::PointLightComponent>();
				scene.attachComponent(light);
				light->setPosition(mPos);
				light->setOrigin(sf::Vector2f(lightTexture.getSize().x * 0.5f, lightTexture.getSize().y * 0.5f));
				light->setPosition(ke::Application::getPointerPositionView(scene.getView()));
				light->setColor(sf::Color(200, 200, 10));
				light->setIntensity(5.f);
			}
		}
	});

	ke::Application::setUpdateDefaultFunction([&](sf::Time dt)
	{
		scene.update(dt);
		if (scene.useLight())
		{
			mouseLight->setPosition(ke::Application::getPointerPositionView(scene.getView()));
		}
		ke::Application::setDebugInfo("Actors", scene.getActorCount());
	});

	ke::Application::setRenderDefaultFunction([&](sf::RenderTarget& target)
	{
		scene.render(target);
		gui.draw();
	});

	ke::Application::runDefault();

	scene.saveToXml("Example/");

	mouseLight = nullptr;
	map = nullptr;
	layer = nullptr;
	actor = nullptr;

	ke::Application::getInputs().saveToFile("Example/inputs.cfg");

	ke::Application::quit();

	return 0;
}