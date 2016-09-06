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

bool MyMap::loadTmxString(std::string const & str)
{
	clearLayers();
	if (str == "")
	{
		return false;
	}
	pugi::xml_document doc;
	if (!doc.load_string(str.c_str()))
	{
		return false;
	}
	std::string path = "";
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

	loadProperties(map);

	for (pugi::xml_node tileset = map.child("tileset"); tileset; tileset = tileset.next_sibling("tileset"))
	{
		mTileset = &getWorld()->createResource<ke::Tileset>(tileset.attribute("name").as_string(), tileset, path);
	}

	for (pugi::xml_node layer = map.child("layer"); layer; layer = layer.next_sibling("layer"))
	{
		addLayer()->loadFromNode(layer, mTileset, mSize, mTileSize, mOrientation, mStaggerAxis, mStaggerIndex, mHexSideLength);
	}

	for (pugi::xml_node imagelayer = map.child("imagelayer"); imagelayer; imagelayer = imagelayer.next_sibling("imagelayer"))
	{
		std::shared_ptr<ke::SpriteComponent> image = addImage();
		sf::Vector2f offset;
		for (const pugi::xml_attribute& attr : imagelayer.attributes())
		{
			if (attr.name() == std::string("offsetx"))
			{
				offset.x = attr.as_float();
			}
			if (attr.name() == std::string("offsety"))
			{
				offset.y = attr.as_float();
			}
			if (attr.name() == std::string("opacity"))
			{
				image->setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(255 * attr.as_float())));
			}
			if (attr.name() == std::string("visible"))
			{
				image->setVisible((attr.value() == "true"));
			}
		}
		image->setPosition(offset);
		pugi::xml_node img = imagelayer.child("image");
		if (img)
		{
			std::string source = img.attribute("source").as_string();
			if (source != "")
			{
				if (!getWorld()->hasResource(source))
				{
					getWorld()->createResource<ke::Texture>(source, path + source);
				}
				image->setTexture(source);
			}
		}
		pugi::xml_node properties = imagelayer.child("properties");
		if (properties)
		{
			for (const pugi::xml_node& property : properties.children("property"))
			{
				if (property.attribute("name").as_string() == std::string("z"))
				{
					image->setZ(property.attribute("value").as_float());
				}
			}
		}
	}

	for (pugi::xml_node group = map.child("objectgroup"); group; group = group.next_sibling("objectgroup"))
	{
		for (pugi::xml_node object = group.child("object"); object; object = object.next_sibling("object"))
		{
			/*
			MyObject::Ptr obj = getWorld().createActor<MyObject>();
			obj->setPosition({ object.attribute("x").as_float(), object.attribute("y").as_float() });
			obj->setSize(object.attribute("width").as_int(), object.attribute("height").as_int());
			*/
		}
	}

	return true;
}
