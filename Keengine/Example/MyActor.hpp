#ifndef MYACTOR_HPP
#define MYACTOR_HPP

#include "../Sources/Core/Actor.hpp"

class MyActor : public ke::Actor
{
    public:
		typedef std::shared_ptr<MyActor> Ptr;

        MyActor(ke::Scene& scene);

		void update(sf::Time dt);

    private:
		ke::PointComponent mA;
		ke::AnimatorComponent mB;
		ke::PointLightComponent mC;
		ke::InputComponent mD;

		bool mRunning;
};

#endif // MYACTOR_HPP
