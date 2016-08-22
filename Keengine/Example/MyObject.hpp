#ifndef MYOBJECT_HPP
#define MYOBJECT_HPP

#include "../Sources/Core/Actor.hpp"

#include "../Sources/Components/ShapeComponent.hpp"

class MyObject : public ke::Actor
{
	public:
		typedef std::shared_ptr<MyObject> Ptr;

		MyObject();

		void setSize(int x, int y);

	private:
		ke::ShapeComponent mShape;
};

#endif // MYOBJECT_HPP