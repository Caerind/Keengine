#include "PhysicSystem.hpp"

namespace ke
{

PhysicSystem::PhysicSystem()
	//: mWorld(b2::Vec2(0.f, 0.f))
{
	mVelocityIterations = 8;
	mPositionIterations = 3;
}

void PhysicSystem::disableGravity()
{
	//mWorld.SetGravity(b2::Vec2(0.f, 0.f));
}

/*
b2::Vec2 PhysicSystem::getGravity()
{
	return mWorld.GetGravity();
}

void PhysicSystem::setGravity(b2::Vec2 gravity)
{
	mWorld.SetGravity(gravity);
}
*/

void PhysicSystem::update(sf::Time dt)
{
	//mWorld.Step(dt.asSeconds(), mVelocityIterations, mPositionIterations);
}

} // namespace ke