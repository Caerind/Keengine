#include "MyObject.hpp"

MyObject::MyObject(ke::Scene& scene)
	: ke::Actor(scene)
	, mShape(nullptr)
{
}

void MyObject::initializeComponents()
{
	mShape = createComponent<ke::ShapeComponent>();
	attachComponent(mShape);
	mShape->setFillColor(sf::Color::Blue);
	mShape->setOutlineColor(sf::Color::Red);
	mShape->setOutlineThickness(1.f);
}

void MyObject::setSize(int x, int y)
{
	auto fx = sf::Vector2f((float)x, 0.f);
	auto fy = sf::Vector2f(0.f, (float)y);
	mShape->setPoints({ { 0.f, 0.f }, fx, fx + fy, fy });
}
