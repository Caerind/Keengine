#ifndef PHYSICSYSTEM_HPP
#define PHYSICSYSTEM_HPP

#include <SFML/System/Time.hpp>

//#include "../ExtLibs/Box2D/Box2D.hpp"

class PhysicSystem
{
	public:
		PhysicSystem();

		void disableGravity();
		//void setGravity(b2::Vec2 gravity = b2::Vec2(0.f, -9.8f));
		//b2::Vec2 getGravity();

		void update(sf::Time dt);

	private:
		//b2::World mWorld;
		int mVelocityIterations;
		int mPositionIterations;
};

#endif // PHYSICSYSTEM_HPP
