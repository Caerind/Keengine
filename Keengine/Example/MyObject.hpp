#ifndef MYOBJECT_HPP
#define MYOBJECT_HPP

#include "../Sources/Core/Actor.hpp"

#include "../Sources/Components/ShapeComponent.hpp"

class MyObject : public Actor
{
	public:
		typedef std::shared_ptr<MyObject> Ptr;

		MyObject();

		void setSize(int x, int y);

	private:
		ShapeComponent mShape;
};

#endif // MYOBJECT_HPP