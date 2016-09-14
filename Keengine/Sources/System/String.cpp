#include "String.hpp"

namespace ke
{

void toLower(std::string& str)
{
    std::transform(str.begin(), str.end(),str.begin(), tolower);
}

void toUpper(std::string& str)
{
    std::transform(str.begin(), str.end(),str.begin(), toupper);
}

std::string split(std::string& base, char separator)
{
    std::size_t found = base.find(separator);
    if (found != std::string::npos)
    {
        std::string t = base.substr(0, found);
        base = base.substr(found + 1);
        return t;
    }
    return "";
}

std::string split(std::string& base, std::string const& separator)
{
    std::size_t found = base.find(separator);
    if (found != std::string::npos)
    {
        std::string t = base.substr(0, found);
        base = base.substr(found + 1);
        return t;
    }
    return "";
}

std::vector<std::string> splitVector(std::string str, std::string const& separator)
{
    std::vector<std::string> v;
    std::size_t found;
    do
    {
        found = str.find(separator);
        if (found != std::string::npos)
        {
            v.push_back(str.substr(0,found));
            str = str.substr(found + 1);
        }
    } while (found != std::string::npos);
    v.push_back(str);
    return v;
}

bool contains(std::string const& str, char c)
{
    return str.find(c) != std::string::npos;
}

bool contains(std::string const& str, std::string const& c)
{
    return str.find(c) != std::string::npos;
}

std::string limitSize(std::string str, std::size_t size)
{
    if (str.size() <= size)
    {
        return str;
    }
    else
    {
        return str.substr(0,size);
    }
}

std::string toString(sf::FloatRect const& rect)
{
    return std::to_string(rect.left) + "," + std::to_string(rect.top) + "," + std::to_string(rect.width) + "," + std::to_string(rect.height);
}

std::string toString(sf::IntRect const& rect)
{
    return std::to_string(rect.left) + "," + std::to_string(rect.top) + "," + std::to_string(rect.width) + "," + std::to_string(rect.height);
}

std::string toString(sf::Color const& color)
{
	std::ostringstream oss;
	oss << std::hex << color.toInteger();
	return oss.str();
}

std::string toString(sf::Vector2f const& v)
{
    return std::to_string(v.x) + "," + std::to_string(v.y);
}

std::string toString(sf::Vector2i const& v)
{
    return std::to_string(v.x) + "," + std::to_string(v.y);
}

sf::FloatRect toFloatRect(std::string str)
{
    sf::FloatRect r;
    r.left = std::stof(split(str,","));
    r.top = std::stof(split(str,","));
    r.width = std::stof(split(str,","));
    r.height = std::stof(str);
    return r;
}

sf::IntRect toIntRect(std::string str)
{
    sf::IntRect r;
    r.left = std::stoi(split(str,","));
    r.top = std::stoi(split(str,","));
    r.width = std::stoi(split(str,","));
    r.height = std::stoi(str);
    return r;
}

sf::Color toColor(std::string str)
{
	if (str != "")
	{
		if (str[0] == '#')
		{
			str.erase(str.begin());
		}
		int hexTrans;
		std::stringstream ss(str);
		ss >> std::hex >> hexTrans;
		if (hexTrans >= 0)
		{
			unsigned char red, green, blue;
			red = hexTrans >> 16;
			green = (hexTrans >> 8) & 0xff;
			blue = hexTrans & 0xff;
			return sf::Color(red, green, blue);
		}
	}
	return sf::Color::Transparent;
}

sf::Vector2f toVector2f(std::string str)
{
    sf::Vector2f v;
    v.x = std::stof(split(str,","));
    v.y = std::stof(str);
    return v;
}

sf::Vector2i toVector2i(std::string str)
{
    sf::Vector2i v;
    v.x = std::stoi(split(str,","));
    v.y = std::stoi(str);
    return v;
}

} // namespace ke