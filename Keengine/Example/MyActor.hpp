#ifndef MYACTOR_HPP
#define MYACTOR_HPP

#include "../Sources/Core/Actor.hpp"
#include "../Sources/Components/PointComponent.hpp"
#include "../Sources/Components/AnimatorComponent.hpp"
#include "../Sources/Components/InputComponent.hpp"

class MyActor : public Actor
{
    public:
        MyActor();
        ~MyActor();

        typedef std::shared_ptr<MyActor> Ptr;

		void update(sf::Time dt);

    private:
        PointComponent mA;
		AnimatorComponent mB;
		InputComponent mD;

		bool mRunning;
};

#endif // MYACTOR_HPP
