#ifndef KE_TRIGGERCOMPONENT_HPP
#define KE_TRIGGERCOMPONENT_HPP

#include <Box2D\Box2D.h>

#include "CollisionComponent.hpp"

namespace ke
{

class TriggerComponent : public CollisionComponent
{
	public:
		TriggerComponent();

		void onRegister();
};

} // namespace ke

#endif // KE_COLLISIONCOMPONENT_HPP
