#include "../Sources/Application/Application.hpp"

#include "../Sources/Core/Scene.hpp"
#include "../Sources/Core/Actor.hpp"
#include "../Sources/Core/Factories.hpp"
#include "../Sources/Core/Map.hpp"

#include "MyActor.hpp"
#include "MyObject.hpp"

#include "../Sources/Components/Components.hpp"

#include <iostream>

int main()
{
	ke::Application::init("Example/");

	ke::Application::loadResources("Example/resources.xml");

	ke::Application::setLang("french");

	tgui::Gui gui(ke::Application::getWindow());
	tgui::Button::Ptr button = ke::Application::getResource<ke::Theme>("css").create("Button");
	button->setPosition(350, 50);
	button->setSize(150, 50);
	button->setText(ke::toString(ke::Application::getSize()));
	button->connect("pressed", []() { ke::Application::getLog() << ke::Application::inLang("hello"); });
	gui.add(button);

	ke::Application::getInputs().setKeyboardMapping("MoveUp", sf::Keyboard::Z, ke::InputType::Hold);
	ke::Application::getInputs().setKeyboardMapping("MoveLeft", sf::Keyboard::Q, ke::InputType::Hold);
	ke::Application::getInputs().setKeyboardMapping("MoveDown", sf::Keyboard::S, ke::InputType::Hold);
	ke::Application::getInputs().setKeyboardMapping("MoveRight", sf::Keyboard::D, ke::InputType::Hold);
	ke::Application::getInputs().setKeyboardMapping("Light", sf::Keyboard::L, ke::InputType::Pressed);
	ke::Application::getInputs().loadFromFile("Example/inputs.cfg");
	
	ke::Factories::registerActor<MyActor>();
	ke::Factories::registerActor<MyObject>();

	ke::Scene scene("main");
	scene.useBackgroundRepeatedTexture("sfml");

	ke::Map::Ptr map = scene.createActor<ke::Map>("map");
	int choice = 2;
	switch (choice)
	{
		case 0: map->loadTmxFile("Example/ortho.tmx"); break;
		case 1: map->loadTmxFile("Example/iso.tmx"); break;
		case 2: map->loadTmxFile("Example/stagg.tmx"); break;
		case 3: map->loadTmxFile("Example/hexa.tmx"); break;
	}
	ke::LayerComponent::Ptr layer = map->getLayer(0);

	int gid = 1;
	ke::Application::setEventDefaultFunction([&](sf::Event const& event)
	{
		gui.handleEvent(event);
		sf::Vector2i c = map->worldToCoords(ke::Application::getMousePositionView(scene.getView()));
		if (event.type == sf::Event::MouseButtonPressed)
		{
			std::vector<sf::Vector2i> n = map->getNeighboors(c, (event.mouseButton.button == sf::Mouse::Right));
			if (layer != nullptr)
			{
				for (std::size_t i = 0; i < n.size(); i++)
				{
					layer->setTileId(n[i], gid);
				}
				gid++;
				if (gid >= 4)
				{
					gid = 1;
				}
			}
		}
	});

	ke::Application::setUpdateDefaultFunction([&](sf::Time dt)
	{
		scene.update(dt);
		sf::Vector2i c = map->worldToCoords(ke::Application::getMousePositionView(scene.getView()));
		ke::Application::setDebugInfo("MouseCoords", c);

		sf::Vector2f mvt;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		{
			mvt.y--;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			mvt.x--;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			mvt.y++;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			mvt.x++;
		}
		scene.getView().move(mvt * 400.f * dt.asSeconds());
	});

	ke::Application::setRenderDefaultFunction([&](sf::RenderTarget& target)
	{
		scene.render(target);
		gui.draw();
	});

	ke::Application::runDefault();

	map = nullptr;
	layer = nullptr;

	ke::Application::getInputs().saveToFile("Example/inputs.cfg");

	ke::Application::quit();

	return 0;
}