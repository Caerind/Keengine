#ifndef MYOBJECT_HPP
#define MYOBJECT_HPP

#include "../Sources/Core/Actor.hpp"

#include "../Sources/Components/ShapeComponent.hpp"

class MyObject : public ke::Actor
{
	public:
		typedef std::shared_ptr<MyObject> Ptr;

		MyObject(ke::Scene& scene);

		void setSize(int x, int y);

	private:
		ke::ShapeComponent::Ptr mShape;
		ke::LightShapeComponent::Ptr mLightShape;
};

#endif // MYOBJECT_HPP