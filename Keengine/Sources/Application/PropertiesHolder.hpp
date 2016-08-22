#ifndef PROPERTIESHOLDER_HPP
#define PROPERTIESHOLDER_HPP

#include <string>
#include <unordered_map>

#include "../ExtLibs/pugixml.hpp"
#include "../System/Variant.hpp"

class PropertiesHolder
{
    public:
		PropertiesHolder();

		template <typename T> void setProperty(std::string const& id, T const& value)
		{
			mProperties[id] = Variant(value);
		}

		Variant getProperty(std::string const& id);

		void loadProperties(pugi::xml_node const& node);
		void saveProperties(pugi::xml_node& node);

		bool propertyExist(std::string const& id) const;

		void removeProperty(std::string const& id);

    protected:
		std::unordered_map<std::string, Variant> mProperties;
};

#endif // PROPERTIESHOLDER_HPP
