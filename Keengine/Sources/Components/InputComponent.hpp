#ifndef KE_INPUTCOMPONENT_HPP
#define KE_INPUTCOMPONENT_HPP

#include "../Core/Component.hpp"
#include "../Core/InputSystem.hpp"

namespace ke
{

class InputComponent : public Input, public Component
{
    public:
        InputComponent();
        ~InputComponent();
};

} // namespace ke

#endif // KE_INPUTCOMPONENT_HPP
