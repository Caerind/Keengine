#ifndef KE_COLLISIONCOMPONENT_HPP
#define KE_COLLISIONCOMPONENT_HPP

#include "../ExtLibs/Box2D/Box2D.h"

#include "../Core/SceneComponent.hpp"

namespace ke
{

class CollisionComponent : public SceneComponent
{
	public:
		typedef std::shared_ptr<CollisionComponent> Ptr;

		CollisionComponent(Actor& actor);

		void onRegister();
		void onUnregister();

		b2Fixture* getFixture();

		// TODO : Shape interface

	protected:
		b2Fixture* mFixture;
};

} // namespace ke

#endif // KE_COLLISIONCOMPONENT_HPP
