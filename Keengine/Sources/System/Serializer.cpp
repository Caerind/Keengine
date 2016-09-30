#include "Serializer.hpp"

namespace ke
{

Serializer::Serializer()
{
}

void Serializer::create(const std::string& identifier)
{
}

void Serializer::save(const std::string& identifier, const std::string& value)
{
}

void Serializer::end()
{
}

bool Serializer::read(const std::string& identifier)
{
	return false;
}

bool Serializer::load(const std::string& identifier, std::string& value)
{
	return false;
}

} // namespace ke