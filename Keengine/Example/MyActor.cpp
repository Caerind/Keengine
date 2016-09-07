#include "MyActor.hpp"
#include "../Sources/Core/Scene.hpp"

MyActor::MyActor(ke::Scene& scene)
	: ke::Actor(scene)
	, mA(nullptr)
	, mB(nullptr)
	, mC(nullptr)
	, mD(nullptr)
	, mMoveCounter(0)
	, mMoving(false)
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
	mD->bindAction("MoveUp", [&](std::vector<std::string> const& data)
	{
		b2Body* body = getBody();
		if (body != nullptr)
		{
			float impulse = body->GetMass() * (-5.f - body->GetLinearVelocity().y);
			body->ApplyLinearImpulse(b2Vec2(0.f, impulse), body->GetWorldCenter(), true);
		}
		mMoveCounter++;
		return false;
	});
	mD->bindAction("MoveRight", [&](std::vector<std::string> const& data)
	{
		mVel += 5.f;
		mMoveCounter++;
		return false;
	});
	mD->bindAction("MoveLeft", [&](std::vector<std::string> const& data)
	{
		mVel -= 5.f;
		mMoveCounter++;
		return false;
	});
	mD->bindAction("Light", [&](std::vector<std::string> const& data)
	{
		mC->setOn(!mC->isOn());
		return false;
	});

	if (mBody != nullptr)
	{
		mE = createComponent<ke::CollisionComponent>();
		attachComponent(mE);
		mE->setShape({ { -10.f, -10.f },{ 10.f, -10.f },{ 10.f, 20.f },{ -10.f, 20.f } });
		mE->setDensity(1.f);
		mBody->SetType(b2_dynamicBody);
		mBody->SetFixedRotation(true);
	}
}

void MyActor::update(sf::Time dt)
{
	if (mMoveCounter == 0 && mMoving)
	{
		mB->playAnimation("idle");
	}
	else if (mMoveCounter != 0 && !mMoving)
	{
		mB->playAnimation("run");
	}
	mMoveCounter = 0;

	b2Body* body = getBody();
	if (body != nullptr)
	{
		float impulse = body->GetMass() * (mVel - body->GetLinearVelocity().x);
		body->ApplyLinearImpulse(b2Vec2(impulse, 0.f), body->GetWorldCenter(), true);
	}
	mVel = 0.f;
}
