#include "MyMap.hpp"
#include "../Sources/Core/World.hpp"
#include "MyObject.hpp"

MyMap::MyMap()
{
	registerComponent(&mSun);
	attachComponent(&mSun);
	mSun.setIntensity(6.f);
	mSun.setDirection({ -0.1f, 0.6f });
}

bool MyMap::loadTmxFile(std::string const& filename)
{
	clearLayers();
	if (filename == "")
	{
		return false;
	}
	pugi::xml_document doc;
	if (!doc.load_file(filename.c_str()))
	{
		return false;
	}
	std::string path;
	std::size_t found = filename.find_last_of("/");
	if (found != std::string::npos)
	{
		path = filename.substr(0, found + 1);
	}
	else
	{
		found = filename.find_last_of("\\");
		if (found != std::string::npos)
		{
			path = filename.substr(0, found + 1);
		}
		else
		{
			path = "";
		}
	}
	pugi::xml_node map = doc.child("map");
	if (!map)
	{
		return false;
	}
	for (pugi::xml_attribute attr = map.first_attribute(); attr; attr = attr.next_attribute())
	{
		if (attr.name() == std::string("orientation")) mOrientation = attr.as_string();
		if (attr.name() == std::string("width")) mSize.x = attr.as_int();
		if (attr.name() == std::string("height")) mSize.y = attr.as_int();
		if (attr.name() == std::string("tilewidth")) mTileSize.x = attr.as_int();
		if (attr.name() == std::string("tileheight")) mTileSize.y = attr.as_int();
		if (attr.name() == std::string("hexsidelength")) mHexSideLength = attr.as_uint();
		if (attr.name() == std::string("staggeraxis")) mStaggerAxis = attr.as_string();
		if (attr.name() == std::string("staggerindex")) mStaggerIndex = attr.as_string();
	}
	pugi::xml_node properties = map.child("properties");
	if (properties)
	{
		for (const pugi::xml_node& property : properties.children("property"))
		{
			std::string name = property.attribute("name").as_string();
			std::string value = property.attribute("value").as_string();
			setProperty(name, value);
		}
	}

	for (pugi::xml_node tileset = map.child("tileset"); tileset; tileset = tileset.next_sibling("tileset"))
	{
		mTileset = &getWorld().createResource<Tileset>(tileset.attribute("name").as_string(), tileset, path);
	}

	for (pugi::xml_node layer = map.child("layer"); layer; layer = layer.next_sibling("layer"))
	{
		addLayer()->loadFromNode(layer, mTileset, mSize, mTileSize, mOrientation, mStaggerAxis, mStaggerIndex, mHexSideLength);
	}

	for (pugi::xml_node group = map.child("objectgroup"); group; group = group.next_sibling("objectgroup"))
	{
		for (pugi::xml_node object = group.child("object"); object; object = object.next_sibling("object"))
		{
			MyObject::Ptr obj = getWorld().createActor<MyObject>();
			obj->setPosition({ object.attribute("x").as_float(), object.attribute("y").as_float() });
			obj->setSize(object.attribute("width").as_int(), object.attribute("height").as_int());
		}
	}
	return true;
}
