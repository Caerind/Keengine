#ifndef KE_TRIGGERCOMPONENT_HPP
#define KE_TRIGGERCOMPONENT_HPP

#include "CollisionComponent.hpp"

namespace ke
{

class TriggerComponent : public CollisionComponent
{
	public:
		typedef std::shared_ptr<TriggerComponent> Ptr;

		TYPE(TriggerComponent)

		TriggerComponent(Actor& actor);

		void onRegister();

		virtual void serialize(Serializer& serializer);
		virtual bool deserialize(Serializer& serializer, const std::string& identifier);
};

} // namespace ke

#endif // KE_COLLISIONCOMPONENT_HPP
