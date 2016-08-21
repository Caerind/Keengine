#include "MyActor.hpp"
#include "../Sources/Core/World.hpp"

MyActor::MyActor()
	: Actor()
	, mA()
	, mC()
	, mD()
{
    registerComponent(&mA);
	attachComponent(&mA);

	registerComponent(&mC);
	attachComponent(&mC);
	mC.setTexture("particle");
	mC.setParticleLifetime(sf::seconds(5.f));
	mC.setParticleColor(sf::Color::Green);
	mC.setParticleLifetime(Distributions::uniform(sf::seconds(1.f), sf::seconds(5.f)));
	mC.setParticleVelocity(Distributions::deflect(sf::Vector2f(0.f, 100.f), 30.f));
	mC.setParticleRotation(Distributions::uniform(0.f, 360.f));
	mC.setParticleRotationSpeed(Distributions::uniform(0.f, 10.f));

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
	mD.bindAction("Emit", [&](std::vector<std::string> const& data)
	{
		getWorld().getLog() << "Actor Emit";
		mC.emitParticle();
		return false;
	});
}

MyActor::~MyActor()
{
}
