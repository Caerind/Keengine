#ifndef KE_INPUTCOMPONENT_HPP
#define KE_INPUTCOMPONENT_HPP

#include "../Core/Component.hpp"

namespace ke
{

class InputComponent : public Input, public Component
{
    public:
		typedef std::shared_ptr<InputComponent> Ptr;

        InputComponent(Actor& actor);

		void onRegister();
		void onUnregister();
};

} // namespace ke

#endif // KE_INPUTCOMPONENT_HPP
