#ifndef MYMAP_HPP
#define MYMAP_HPP

#include "../Sources/Core/Map.hpp"

class MyMap : public ke::Map
{
	public:
		typedef std::shared_ptr<MyMap> Ptr;

		TYPE(MyMap)

		MyMap(ke::Scene& scene);

		bool loadTmxString(std::string const& str);

	private:
		ke::DirectionLightComponent::Ptr mLight;

		sf::Color mSunColor;
		sf::Color mMoonColor;
};

#endif // MYMAP_HPP