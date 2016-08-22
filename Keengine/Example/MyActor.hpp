#ifndef MYACTOR_HPP
#define MYACTOR_HPP

#include "../Sources/Core/Actor.hpp"
#include "../Sources/Components/PointComponent.hpp"
#include "../Sources/Components/AnimatorComponent.hpp"
#include "../Sources/Components/InputComponent.hpp"
#include "../Sources/Components/PointLightComponent.hpp"

class MyActor : public ke::Actor
{
    public:
        MyActor();
        ~MyActor();

        typedef std::shared_ptr<MyActor> Ptr;

		void update(sf::Time dt);

    private:
		ke::PointComponent mA;
		ke::AnimatorComponent mB;
		ke::PointLightComponent mC;
		ke::InputComponent mD;

		bool mRunning;
};

#endif // MYACTOR_HPP
