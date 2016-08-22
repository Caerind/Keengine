#ifndef MYMAP_HPP
#define MYMAP_HPP

#include "../Sources/Core/Map.hpp"
#include "../Sources/Components/DirectionLightComponent.hpp"

class MyMap : public Map
{
	public:
		typedef std::shared_ptr<MyMap> Ptr;

		MyMap();

		bool loadTmxFile(std::string const& filename);

	private:
		DirectionLightComponent mSun;
};

#endif // MYMAP_HPP