#include "../Sources/Application/Application.hpp"

#include "../Sources/Core/Scene.hpp"
#include "../Sources/Core/Actor.hpp"
#include "../Sources/Core/Factories.hpp"
#include "../Sources/Core/Map.hpp"
#include "../Sources/Core/Pathfinding.hpp"

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
	int choice = 0;
	switch (choice)
	{
		case 0: map->loadTmxFile("Example/ortho.tmx"); break;
		case 1: map->loadTmxFile("Example/iso.tmx"); break;
		case 2: map->loadTmxFile("Example/stagg.tmx"); break;
		case 3: map->loadTmxFile("Example/hexa.tmx"); break;
	}
	map->useForPathFinding(true);

	sf::Clock clock;
	unsigned int id = 0;
	sf::Vector2i begin;
	sf::Vector2i end;
	std::vector<sf::Vector2i> path;

	ke::Application::setEventDefaultFunction([&](sf::Event const& event)
	{
		gui.handleEvent(event);
		sf::Vector2i c = map->worldToCoords(ke::Application::getMousePositionView(scene.getView()));
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				begin = c;
			}
			else
			{
				end = c;
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

		// This is for threaded pathfinding
		if (begin != sf::Vector2i() && end != sf::Vector2i() && id == 0)
		{
			clock.restart();
			id = ke::PathFinding::startPath(begin, end);
			begin = sf::Vector2i();
			end = sf::Vector2i();
			ke::Log::instance() << ke::Variant("Path : started");
		}
		if (id != 0)
		{
			if (ke::PathFinding::calculatedPath(id))
			{
				path = ke::PathFinding::getPath(id);
				ke::Log::instance() << ke::Variant("Path : ended in : ", clock.restart(), "s for a ", path.size(), " sized path");
				id = 0;
			}
		}

		// Otherwise, for direct pathfinding you can use :
		/*
		if (begin != sf::Vector2i() && end != sf::Vector2i())
		{
			clock.restart();
			path = ke::PathFinding::pathfinding(begin, end);
			begin = sf::Vector2i();
			end = sf::Vector2i();
			ke::Log::instance() << ke::Variant("Path : ended in ", clock.getElapsedTime());
		}
		*/
	});

	ke::Application::setRenderDefaultFunction([&](sf::RenderTarget& target)
	{
		scene.render(target);
		gui.draw();
		for (std::size_t i = 0; i < path.size(); i++)
		{
			sf::CircleShape s(4.f);
			s.setPosition(map->coordsToWorld(path[i]));
			s.move(map->getTileSize().x * 0.5f, map->getTileSize().y * 0.5f);
			s.setFillColor(sf::Color::Red);
			target.draw(s);
		}
	});

	ke::Application::runDefault();

	map = nullptr;

	ke::Application::getInputs().saveToFile("Example/inputs.cfg");

	ke::Application::quit();

	return 0;
}