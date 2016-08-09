#include "MyActor.hpp"

MyActor::MyActor()
: Actor()
, mA()
, mB()
, mC()
{
    registerComponent(&mA);
	attachComponent(&mA);
	mA.setZ(1000.f);
	mA.setPosition(sf::Vector2f(-100.f, -100.f));

	registerComponent(&mB);
	attachComponent(&mB);
	mB.setTexture("sfml");
	mB.setPosition(sf::Vector2f(-100.f, -100.f));

	registerComponent(&mC);
	mB.attachComponent(&mC);
	mC.setTexture("sfml");
	mC.setPosition(sf::Vector2f(-100.f, -100.f));
	mC.setZ(100.f);
}

MyActor::~MyActor()
{
}
