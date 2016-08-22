#ifndef MYMAP_HPP
#define MYMAP_HPP

#include "../Sources/Core/Map.hpp"
#include "../Sources/Components/DirectionLightComponent.hpp"

class MyMap : public ke::Map
{
	public:
		typedef std::shared_ptr<MyMap> Ptr;

		MyMap();

		bool loadTmxString(std::string const& str);

	private:
		ke::DirectionLightComponent mSun;
};

#endif // MYMAP_HPP