#include "ValueContainer.hpp"

namespace ah
{

ValueContainer::ValueContainer()
: mValues()
{
}

bool ValueContainer::exist(std::string const& id) const
{
    return (mValues.find(id) != mValues.end());
}

void ValueContainer::set(std::string const& id, std::string const& value)
{
    mValues[id].first = value;
}

void ValueContainer::set(std::string const& id, std::string const& value, bool save)
{
    set(id,value);
    setSaved(id,save);
}

std::string ValueContainer::get(std::string const& id) const
{
    if (!exist(id))
    {
        return "";
    }
    return mValues.at(id).first;
}

void ValueContainer::setInt(std::string const& id, int value)
{
    mValues[id].first = std::to_string(value);
}

void ValueContainer::setInt(std::string const& id, int value, bool save)
{
    setInt(id,value);
    setSaved(id,save);
}

int ValueContainer::getInt(std::string const& id) const
{
    if (!exist(id))
    {
        return 0;
    }
    return std::stoi(mValues.at(id).first);
}

void ValueContainer::setFloat(std::string const& id, float value)
{
    mValues[id].first = std::to_string(value);
}

void ValueContainer::setFloat(std::string const& id, float value, bool save)
{
    setFloat(id,value);
    setSaved(id,save);
}

float ValueContainer::getFloat(std::string const& id) const
{
    if (!exist(id))
    {
        return 0.f;
    }
    return std::stof(mValues.at(id).first);
}

void ValueContainer::setSaved(std::string const& id, bool save)
{
    mValues[id].second = save;
}

bool ValueContainer::isSaved(std::string const& id) const
{
    if (!exist(id))
    {
        return false;
    }
    return mValues.at(id).second;
}

bool ValueContainer::load(std::string const& filename)
{
    pugi::xml_document doc;
    if (!doc.load_file(filename.c_str()))
    {
        return false;
    }
    pugi::xml_node values = doc.child("Values");
    if (values)
    {
        for (pugi::xml_node v = values.child("Value"); v; v = v.next_sibling("Value"))
        {
            set(v.attribute("id").value(),v.attribute("value").value(),true);
        }
        return true;
    }
    return false;
}

void ValueContainer::save(std::string const& filename)
{
    pugi::xml_document doc;
    doc.load_file(filename.c_str());
    if (doc.child("Values"))
    {
        doc.remove_child("Values");
    }
    pugi::xml_node values = doc.append_child("Values");
    for (auto itr = mValues.begin(); itr != mValues.end(); itr++)
    {
        pugi::xml_node v = values.append_child("Value");
        v.append_attribute("id") = itr->first.c_str();
        v.append_attribute("value") = itr->second.first.c_str();
    }
    doc.save_file(filename.c_str());
}

} // namespace ah
