#ifndef MYOBJECT_HPP
#define MYOBJECT_HPP

#include "../Sources/Core/Actor.hpp"

#include "../Sources/Components/ShapeComponent.hpp"

class MyObject : public ke::Actor
{
	public:
		typedef std::shared_ptr<MyObject> Ptr;

		TYPE(MyObject)

		MyObject(ke::Scene& scene);

		void initializeComponents();

		void setSize(int x, int y);

	private:
		ke::ShapeComponent::Ptr mShape;
		ke::LightShapeComponent::Ptr mLightShape;
		ke::CollisionComponent::Ptr mCollision;
};

#endif // MYOBJECT_HPP