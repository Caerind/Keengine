#include "Serializable.hpp"
#include "Serializer.hpp"

namespace ke
{

Serializable::Serializable()
{
}

bool Serializable::serialize(Serializer& serializer, const std::string& identifier)
{
	return true;
}

bool Serializable::deserialize(Serializer& serializer, const std::string& identifier)
{
	return true;
}

} // namespace ke