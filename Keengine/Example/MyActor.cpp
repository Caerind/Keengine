#include "MyActor.hpp"
#include "../Sources/Core/World.hpp"

MyActor::MyActor()
	: Actor()
	, mA()
	, mB()
	, mD()
	, mRunning(false)
{
    registerComponent(&mA);
	attachComponent(&mA);

	registerComponent(&mB);
	attachComponent(&mB);
	Animation& idle = mB.getAnimation("idle");
	idle.addFrame("cat", { 0, 0, 64, 64 }, sf::seconds(0.15f));
	idle.addFrame("cat", { 64, 0, 64, 64 }, sf::seconds(0.15f));
	idle.addFrame("cat", { 128, 0, 64, 64 }, sf::seconds(0.15f));
	idle.addFrame("cat", { 192, 0, 64, 64 }, sf::seconds(0.15f));
	Animation& run = mB.getAnimation("run");
	run.addFrame("cat", { 0, 64, 64, 64 }, sf::seconds(0.15f));
	run.addFrame("cat", { 64, 64, 64, 64 }, sf::seconds(0.15f));
	run.addFrame("cat", { 128, 64, 64, 64 }, sf::seconds(0.15f));
	run.addFrame("cat", { 192, 64, 64, 64 }, sf::seconds(0.15f));
	run.addFrame("cat", { 256, 64, 64, 64 }, sf::seconds(0.15f));
	run.addFrame("cat", { 320, 64, 64, 64 }, sf::seconds(0.15f));
	run.addFrame("cat", { 384, 64, 64, 64 }, sf::seconds(0.15f));
	run.addFrame("cat", { 448, 64, 64, 64 }, sf::seconds(0.15f));

	registerComponent(&mD);
	mD.bindAction("MoveRight", [&](std::vector<std::string> const& data)
	{
		if (!mRunning)
		{
			mB.stopAnimation();
			mB.playAnimation("run");
			mRunning = true;
		}
		return false;
	});
	mD.bindAction("Stop", [&](std::vector<std::string> const& data)
	{
		if (mRunning)
		{
			mB.stopAnimation();
			mB.playAnimation("idle");
			mRunning = false;
		}
		return false;
	});
}

MyActor::~MyActor()
{
}

void MyActor::update(sf::Time dt)
{
	if (mRunning)
	{
		move(sf::Vector2f(1.f, 0.f) * 100.f * dt.asSeconds());
	}
}
