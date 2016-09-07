#include "MyActor.hpp"
#include "../Sources/Core/Scene.hpp"

MyActor::MyActor(ke::Scene& scene)
	: ke::Actor(scene)
	, mA(nullptr)
	, mB(nullptr)
	, mC(nullptr)
	, mD(nullptr)
	, mRunningRight(false)
	, mRunningLeft(false)
{
	mA = createComponent<ke::PointComponent>();
	attachComponent(mA);

	mB = createComponent<ke::AnimatorComponent>();
	attachComponent(mB);
	mB->setPosition(-32.f, -32.f);
	ke::Animation& idle = mB->getAnimation("idle");
	idle.addFrame("cat", { 0, 0, 64, 64 }, sf::seconds(0.15f));
	idle.addFrame("cat", { 64, 0, 64, 64 }, sf::seconds(0.15f));
	idle.addFrame("cat", { 128, 0, 64, 64 }, sf::seconds(0.15f));
	idle.addFrame("cat", { 192, 0, 64, 64 }, sf::seconds(0.15f));
	ke::Animation& run = mB->getAnimation("run");
	run.addFrame("cat", { 0, 64, 64, 64 }, sf::seconds(0.15f));
	run.addFrame("cat", { 64, 64, 64, 64 }, sf::seconds(0.15f));
	run.addFrame("cat", { 128, 64, 64, 64 }, sf::seconds(0.15f));
	run.addFrame("cat", { 192, 64, 64, 64 }, sf::seconds(0.15f));
	run.addFrame("cat", { 256, 64, 64, 64 }, sf::seconds(0.15f));
	run.addFrame("cat", { 320, 64, 64, 64 }, sf::seconds(0.15f));
	run.addFrame("cat", { 384, 64, 64, 64 }, sf::seconds(0.15f));
	run.addFrame("cat", { 448, 64, 64, 64 }, sf::seconds(0.15f));
	mB->playAnimation("idle");

	mC = createComponent<ke::PointLightComponent>();
	attachComponent(mC);
	mC->setColor(sf::Color(200,200,10));
	mC->setIntensity(5.f);

	mD = createComponent<ke::InputComponent>();
	mD->bindAction("MoveRight", [&](std::vector<std::string> const& data)
	{
		mB->stopAnimation();
		mB->playAnimation("run");
		mRunningRight = true;
		return false;
	});
	mD->bindAction("StopRight", [&](std::vector<std::string> const& data)
	{
		mB->stopAnimation();
		mB->playAnimation("idle");
		mRunningRight = false;
		return false;
	});
	mD->bindAction("MoveLeft", [&](std::vector<std::string> const& data)
	{
		mB->stopAnimation();
		mB->playAnimation("run");
		mRunningLeft = true;
		return false;
	});
	mD->bindAction("StopLeft", [&](std::vector<std::string> const& data)
	{
		mB->stopAnimation();
		mB->playAnimation("idle");
		mRunningLeft = false;
		return false;
	});
}

void MyActor::update(sf::Time dt)
{
	if (mRunningRight)
	{
		move(sf::Vector2f(1.f, 0.f) * 100.f * dt.asSeconds());
	}
	if (mRunningLeft)
	{
		move(sf::Vector2f(-1.f, 0.f) * 100.f * dt.asSeconds());
	}
}
