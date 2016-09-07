#include "MyObject.hpp"

MyObject::MyObject(ke::Scene& scene)
	: ke::Actor(scene)
	, mShape(nullptr)
{
	mShape = createComponent<ke::ShapeComponent>();
	attachComponent(mShape);
	mShape->setPointCount(4);
	mShape->setPoint(0, sf::Vector2f());
	mShape->setFillColor(sf::Color::Blue);
	mShape->setOutlineColor(sf::Color::Red);
	mShape->setOutlineThickness(1.f);

	mLightShape = createComponent<ke::LightShapeComponent>();
	attachComponent(mLightShape);
	mLightShape->setPointCount(4);
	mLightShape->setPoint(0, sf::Vector2f());
	mLightShape->setOutlineThickness(1.f);
}

void MyObject::setSize(int x, int y)
{
	auto fx = sf::Vector2f((float)x, 0.f);
	auto fy = sf::Vector2f(0.f, (float)y);
	mShape->setPoint(1, fx);
	mShape->setPoint(2, fx + fy);
	mShape->setPoint(3, fy);
	mLightShape->setPoint(1, fx);
	mLightShape->setPoint(2, fx + fy);
	mLightShape->setPoint(3, fy);
}
