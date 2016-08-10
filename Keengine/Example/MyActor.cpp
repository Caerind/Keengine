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

	registerComponent(&mB);
	attachComponent(&mB);
	mB.setZ(100.f);
	mB.setTexture("sfml");

	registerComponent(&mC);
	attachComponent(&mC);
	mC.setTexture("particle");
	mC.setEmissionRate(30.f);
	mC.setParticleLifetime(sf::seconds(5.f));
	mC.setParticlePosition(sf::Vector2f(0.f, 0.f));
	mC.setParticleVelocity(sf::Vector2f(10.f, 10.f));
}

MyActor::~MyActor()
{
}
