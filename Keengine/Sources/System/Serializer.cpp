#include "Serializer.hpp"

namespace ke
{

Serializer::Serializer()
{
}

Serializer::~Serializer()
{
}

bool Serializer::openDocument(const std::string& filename, bool erase, const std::string& root)
{
	bool ret = true;
	mFilename = filename;
	if (erase)
	{
		mDoc.append_child(root.c_str());
		saveDocument();
	}
	else
	{
		std::ifstream file(filename);
		if (file)
		{
			mDoc.load(file);
			if (!mDoc.child(root.c_str()))
			{
				mDoc.append_child(root.c_str());
			}
		}
		else
		{
			mDoc.append_child(root.c_str());
			ret = false;
		}
		file.close();
	}

	mActualNode = mDoc.child(root.c_str());
	return ret;
}

void Serializer::saveDocument(bool readable)
{
	if (readable)
	{
		mDoc.save_file(mFilename.c_str());
	}
	else
	{
		mDoc.save_file(mFilename.c_str(), "");
	}
}

void Serializer::create(const std::string& identifier)
{
	mActualNode = mActualNode.append_child(identifier.c_str());
}

void Serializer::save(const std::string& identifier, const std::string& value)
{
	if (mActualNode.attribute(identifier.c_str()))
	{
		mActualNode.attribute(identifier.c_str()) = value.c_str();
	}
	else
	{
		mActualNode.append_attribute(identifier.c_str()) = value.c_str();
	}
}

void Serializer::save(const std::string& identifier, const int& value)
{
	save(identifier, toString<int>(value));
}

void Serializer::save(const std::string& identifier, const unsigned int& value)
{
	save(identifier, toString<unsigned int>(value));
}

void Serializer::save(const std::string& identifier, const char& value)
{
	save(identifier, toString<char>(value));
}

void Serializer::save(const std::string& identifier, const float& value)
{
	save(identifier, toString<float>(value));
}

void Serializer::save(const std::string& identifier, const bool& value)
{
	save(identifier, toString<bool>(value));
}

void Serializer::save(const std::string& identifier, const sf::Vector2f& value)
{
	save(identifier, toString<sf::Vector2f>(value));
}

void Serializer::save(const std::string& identifier, const sf::Vector2i& value)
{
	save(identifier, toString<sf::Vector2i>(value));
}

void Serializer::save(const std::string& identifier, const sf::Color& value)
{
	save(identifier, toString<sf::Color>(value));
}

void Serializer::save(const std::string& identifier, const sf::IntRect& value)
{
	save(identifier, toString<sf::IntRect>(value));
}

void Serializer::save(const std::string& identifier, const sf::FloatRect& value)
{
	save(identifier, toString<sf::FloatRect>(value));
}

void Serializer::save(const std::string& identifier, const sf::Time& value)
{
	save(identifier, toString<sf::Time>(value));
}

void Serializer::end()
{
	mActualNode = mActualNode.parent();
}

bool Serializer::read(const std::string& identifier)
{
	if (mActualNode.child(identifier.c_str()))
	{
		mActualNode = mActualNode.child(identifier.c_str());
		return true;
	}
	return false;
}

bool Serializer::load(const std::string& identifier, std::string& value)
{
	if (mActualNode.attribute(identifier.c_str()))
	{
		value = mActualNode.attribute(identifier.c_str()).value();
		return true;
	}
	return false;
}

bool Serializer::load(const std::string& identifier, int& value)
{
	std::string temp;
	if (load(identifier, temp))
	{
		value = fromString<int>(temp);
		return true;
	}
	return false;
}

bool Serializer::load(const std::string& identifier, unsigned int& value)
{
	std::string temp;
	if (load(identifier, temp))
	{
		value = fromString<unsigned int>(temp);
		return true;
	}
	return false;
}

bool Serializer::load(const std::string& identifier, char& value)
{
	std::string temp;
	if (load(identifier, temp))
	{
		value = fromString<char>(temp);
		return true;
	}
	return false;
}

bool Serializer::load(const std::string& identifier, float& value)
{
	std::string temp;
	if (load(identifier, temp))
	{
		value = fromString<float>(temp);
		return true;
	}
	return false;
}

bool Serializer::load(const std::string& identifier, bool& value)
{
	std::string temp;
	if (load(identifier, temp))
	{
		value = fromString<bool>(temp);
		return true;
	}
	return false;
}

bool Serializer::load(const std::string& identifier, sf::Vector2f& value)
{
	std::string temp;
	if (load(identifier, temp))
	{
		value = fromString<sf::Vector2f>(temp);
		return true;
	}
	return false;
}

bool Serializer::load(const std::string& identifier, sf::Vector2i& value)
{
	std::string temp;
	if (load(identifier, temp))
	{
		value = fromString<sf::Vector2i>(temp);
		return true;
	}
	return false;
}

bool Serializer::load(const std::string& identifier, sf::Color& value)
{
	std::string temp;
	if (load(identifier, temp))
	{
		value = fromString<sf::Color>(temp);
		return true;
	}
	return false;
}

bool Serializer::load(const std::string& identifier, sf::IntRect& value)
{
	std::string temp;
	if (load(identifier, temp))
	{
		value = fromString<sf::IntRect>(temp);
		return true;
	}
	return false;
}

bool Serializer::load(const std::string& identifier, sf::FloatRect& value)
{
	std::string temp;
	if (load(identifier, temp))
	{
		value = fromString<sf::FloatRect>(temp);
		return true;
	}
	return false;
}

bool Serializer::load(const std::string & identifier, sf::Time & value)
{
	std::string temp;
	if (load(identifier, temp))
	{
		value = fromString<sf::Time>(temp);
		return true;
	}
	return false;
}

std::string Serializer::load(const std::string& identifier)
{
	std::string temp = "";
	load(identifier, temp);
	return temp;
}

} // namespace ke