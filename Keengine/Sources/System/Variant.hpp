#ifndef KE_VARIANT_HPP
#define KE_VARIANT_HPP

#include "String.hpp"

namespace ke
{

class Variant : public std::string
{
	public:
		template <typename T>
		Variant(const T& value) : std::string(toString<T>(value))
		{}

		template <typename T> bool operator==(const T& value) const
		{
		    return this->compare(Variant(value)) == 0;
		}

		bool operator==(const char* value) const
		{
		    return this->compare(value) == 0;
		}

		template <typename T>
		T as()
		{
		    return fromString<T>(*this);
		}
};

} // namespace ke

#endif // KE_VARIANT_HPP
