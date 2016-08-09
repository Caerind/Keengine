#ifndef MYACTOR_HPP
#define MYACTOR_HPP

#include "../Sources/Core/Actor.hpp"
#include "../Sources/Components/PointComponent.hpp"
#include "../Sources/Components/SpriteComponent.hpp"

class MyActor : public Actor
{
    public:
        MyActor();
        ~MyActor();

        typedef std::shared_ptr<MyActor> Ptr;

    private:
        PointComponent mA;
        SpriteComponent mB;
		SpriteComponent mC;
};

#endif // MYACTOR_HPP
