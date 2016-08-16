#ifndef PROPERTIESHOLDER_HPP
#define PROPERTIESHOLDER_HPP

#include <map>
#include <string>
#include "../System/Variant.hpp"

class PropertiesHolder
{
    public:
		PropertiesHolder();

		template <typename T> void setProperty(std::string const& id, T const& value)
		{
			mValues[id] = Variant(value);
		}

		Variant getProperty(std::string const& id);

		bool propertyExist(std::string const& id) const;

		void removeProperty(std::string const& id);

    protected:
        std::map<std::string, Variant> mProperties;
};

#endif // PROPERTIESHOLDER_HPP
