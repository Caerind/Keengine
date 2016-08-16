#include "PropertiesHolder.hpp"

PropertiesHolder::PropertiesHolder()
{
}

Variant PropertiesHolder::getProperty(std::string const& id)
{
	return mProperties[id];
}

bool PropertiesHolder::propertyExist(std::string const& id) const
{
	return (mProperties.find(id) != mProperties.end());
}

void PropertiesHolder::removeProperty(std::string const& id)
{
	auto itr = mProperties.find(id);
	if (itr != mProperties.end())
	{
		mProperties.erase(itr);
	}
}
