#ifndef MYACTOR_HPP
#define MYACTOR_HPP

#include "../Sources/Core/Actor.hpp"

class MyActor : public ke::Actor
{
    public:
		typedef std::shared_ptr<MyActor> Ptr;

		TYPE(MyActor)

        MyActor(ke::Scene& scene);

		void initializePhysic();
		void initializeComponents();

		void update(sf::Time dt);

    private:
		ke::NodeComponent::Ptr mA;
		ke::AnimatorComponent::Ptr mB;
		ke::PointLightComponent::Ptr mC;
		ke::InputComponent::Ptr mD;
		ke::PhysicComponent::Ptr mE;
		ke::CameraComponent::Ptr mCam;

		bool mMoving;

		float mVel;
};

#endif // MYACTOR_HPP
