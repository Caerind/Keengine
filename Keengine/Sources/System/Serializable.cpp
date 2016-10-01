#include "Serializable.hpp"
#include "Serializer.hpp"

namespace ke
{

Serializable::Serializable()
{
}

void Serializable::serialize(Serializer& serializer)
{
}

bool Serializable::deserialize(Serializer& serializer, const std::string& identifier)
{
	return true;
}

} // namespace ke