#include "ValueContainer.hpp"

ValueContainer::ValueContainer() 
{
}

Variant ValueContainer::get(std::string const& id)
{
	return mValues[id];
}

bool ValueContainer::exist(std::string const& id) const
{
	return (mValues.find(id) != mValues.end());
}

void ValueContainer::remove(std::string const& id)
{
	auto itr = mValues.find(id);
	if (itr != mValues.end())
	{
		mValues.erase(itr);
	}
}
