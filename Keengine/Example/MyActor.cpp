#include "MyActor.hpp"

MyActor::MyActor()
	: Actor()
	, mA()
	, mB()
	, mC()
	, mD()
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

	registerComponent(&mD);
	mD.bindAction("MoveUp", [&](std::vector<std::string> const& data)
	{
		if (data.size() > 0)
		{
			float dt = std::stof(data[0]);
			float speed = 100.f * dt;
			move(sf::Vector2f(0.f, -1.f) * speed);
		}
		return false;
	});
	mD.bindAction("MoveLeft", [&](std::vector<std::string> const& data)
	{
		if (data.size() > 0)
		{
			float dt = std::stof(data[0]);
			float speed = 100.f * dt;
			move(sf::Vector2f(-1.f, 0.f) * speed);
		}
		return false;
	});
	mD.bindAction("MoveDown", [&](std::vector<std::string> const& data)
	{
		if (data.size() > 0)
		{
			float dt = std::stof(data[0]);
			float speed = 100.f * dt;
			move(sf::Vector2f(0.f, 1.f) * speed);
		}
		return false;
	});
	mD.bindAction("MoveRight", [&](std::vector<std::string> const& data)
	{
		if (data.size() > 0)
		{
			float dt = std::stof(data[0]);
			float speed = 100.f * dt;
			move(sf::Vector2f(1.f, 0.f) * speed);
		}
		return false;
	});
}

MyActor::~MyActor()
{
}
