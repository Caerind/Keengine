#ifndef KE_INPUTCOMPONENT_HPP
#define KE_INPUTCOMPONENT_HPP

#include "../Core/Component.hpp"

namespace ke
{

class InputComponent : public Input, public Component
{
    public:
		typedef std::shared_ptr<InputComponent> Ptr;

		TYPE(InputComponent)

        InputComponent(Actor& actor);

		void onRegister();
		void onUnregister();

		virtual void serialize(Serializer& serializer);
		virtual bool deserialize(Serializer& serializer, const std::string& identifier);
};

} // namespace ke

#endif // KE_INPUTCOMPONENT_HPP
