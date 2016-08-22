#include "PropertiesHolder.hpp"

namespace ke
{

PropertiesHolder::PropertiesHolder()
{
}

Variant PropertiesHolder::getProperty(std::string const& id)
{
	return mProperties[id];
}

void PropertiesHolder::loadProperties(pugi::xml_node const& node)
{
	pugi::xml_node prop = node.child("properties");
	if (prop)
	{
		for (const pugi::xml_node& property : prop.children("property"))
		{
			std::string name = property.attribute("name").as_string();
			std::string value = property.attribute("value").as_string();
			setProperty(name, value);
		}
	}
}

void PropertiesHolder::saveProperties(pugi::xml_node & node)
{
	if (mProperties.size() > 0)
	{
		pugi::xml_node properties = node.append_child("properties");
		for (auto itr = mProperties.begin(); itr != mProperties.end(); itr++)
		{
			pugi::xml_node property = properties.append_child("property");
			property.append_attribute("name") = itr->first.c_str();
			property.append_attribute("value") = itr->second.c_str();
		}
	}
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

} // namespace ke