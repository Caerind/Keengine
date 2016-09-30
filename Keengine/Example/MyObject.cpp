#include "MyObject.hpp"

MyObject::MyObject(ke::Scene& scene)
	: ke::Actor(scene)
	, mShape(nullptr)
	, mLightShape(nullptr)
	, mCollision(nullptr)
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

	if (mBody != nullptr)
	{
		mCollision = createComponent<ke::CollisionComponent>();
		attachComponent(mCollision);
	}
}

void MyObject::setSize(int x, int y)
{
	auto fx = sf::Vector2f((float)x, 0.f);
	auto fy = sf::Vector2f(0.f, (float)y);
	if (mShape != nullptr)
	{
		mShape->setPoint(1, fx);
		mShape->setPoint(2, fx + fy);
		mShape->setPoint(3, fy);
	}
	if (mLightShape != nullptr)
	{
		mLightShape->setPoint(1, fx);
		mLightShape->setPoint(2, fx + fy);
		mLightShape->setPoint(3, fy);
	}
	if (mCollision != nullptr)
	{
		mCollision->setShape({ { 0.f, 0.f }, fx, fx + fy, fy });
	}
}
