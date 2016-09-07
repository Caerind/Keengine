#ifndef KE_TRIGGERCOMPONENT_HPP
#define KE_TRIGGERCOMPONENT_HPP

#include "CollisionComponent.hpp"

namespace ke
{

class TriggerComponent : public CollisionComponent
{
	public:
		typedef std::shared_ptr<TriggerComponent> Ptr;

		TriggerComponent(Actor& actor);

		void onRegister();
};

} // namespace ke

#endif // KE_COLLISIONCOMPONENT_HPP
