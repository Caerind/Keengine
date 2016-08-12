#ifndef INPUTCOMPONENT_HPP
#define INPUTCOMPONENT_HPP

#include "../Core/Component.hpp"
#include "../Core/InputSystem.hpp"

class InputComponent : public Input, public Component
{
    public:
        InputComponent();
        ~InputComponent();
};

#endif // INPUTCOMPONENT_HPP
