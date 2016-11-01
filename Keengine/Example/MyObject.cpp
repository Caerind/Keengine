#include "MyObject.hpp"

MyObject::MyObject(ke::Scene& scene)
	: ke::Actor(scene)
	, mShape(nullptr)
	, mLight(nullptr)
	, mPhysic(nullptr)
{
}

void MyObject::initializeComponents()
{
	mShape = createComponent<ke::ShapeComponent>();
	attachComponent(mShape);
	mShape->setFillColor(sf::Color::Blue);
	mShape->setOutlineColor(sf::Color::Red);
	mShape->setOutlineThickness(1.f);

	mLight = createComponent<ke::LightShapeComponent>();
	attachComponent(mLight);

	mPhysic = createComponent<ke::PhysicComponent>();
	attachComponent(mPhysic);
}

void MyObject::setSize(int x, int y)
{
	auto fx = sf::Vector2f((float)x, 0.f);
	auto fy = sf::Vector2f(0.f, (float)y);
	std::vector<sf::Vector2f> points = { { 0.f, 0.f }, fx, fx + fy, fy };
	mShape->setPoints(points);
	mPhysic->setPoints(points);
	mLight->setPoints(points);
}
