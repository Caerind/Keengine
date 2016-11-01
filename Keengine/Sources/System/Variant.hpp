#ifndef KE_VARIANT_HPP
#define KE_VARIANT_HPP

#include "String.hpp"

namespace ke
{

class Variant : public std::string
{
	public:
		Variant() : std::string("")
		{
		}

		template <typename T>
		Variant(const T& value) : std::string(toString<T>(value))
		{
		}

		template <typename T1, typename T2>
		Variant(const T1& v1, const T2& v2) : std::string(toString<T1>(v1) + toString<T2>(v2))
		{
		}

		template <typename T1, typename T2, typename T3>
		Variant(const T1& v1, const T2& v2, const T3& v3) : std::string(toString<T1>(v1) + toString<T2>(v2) + toString<T3>(v3))
		{
		}

		template <typename T1, typename T2, typename T3, typename T4>
		Variant(const T1& v1, const T2& v2, const T3& v3, const T4& v4) : std::string(toString<T1>(v1) + toString<T2>(v2) + toString<T3>(v3) + toString<T4>(v4))
		{
		}

		// TODO : More than 4 values ?

		template <typename T> bool operator==(const T& value) const
		{
		    return this->compare(Variant(value)) == 0;
		}

		bool operator==(const char* value) const
		{
		    return this->compare(value) == 0;
		}

		template <typename T>
		T as() const
		{
		    return fromString<T>(*this);
		}
};

} // namespace ke

#endif // KE_VARIANT_HPP
