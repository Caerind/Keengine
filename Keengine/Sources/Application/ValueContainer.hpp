#ifndef VALUECONTAINER_HPP
#define VALUECONTAINER_HPP

#include <map>
#include <string>
#include "../System/Variant.hpp"

class ValueContainer
{
    public:
		ValueContainer();

		template <typename T> void set(std::string const& id, T const& value)
		{
			mValues[id] = Variant(value);
		}

		Variant get(std::string const& id);

		bool exist(std::string const& id) const;

		void remove(std::string const& id);

    protected:
        std::map<std::string,Variant> mValues;
};

#endif // VALUECONTAINER_HPP
