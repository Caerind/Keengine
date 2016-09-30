#ifndef KE_VARIANT_HPP
#define KE_VARIANT_HPP

#include "String.hpp"

namespace ke
{

class Variant : public std::string
{
	public:
		template <typename T>
		Variant(const T &t) : std::string(std::to_string(t))
		{}

		Variant(bool boolean) : std::string(toString<bool>(boolean))
		{}

		template <size_t N>
		Variant(const char(&s)[N]) : std::string(s, N)
		{}

		Variant(const char *cstr) : std::string(cstr)
		{}

		Variant(const std::string &other = std::string()) : std::string(other)
		{}

		template <typename T>
		Variant(sf::Vector2<T> const& vector) : std::string(toString(vector))
		{}

		Variant(sf::Color const& color) : std::string(toString(color))
		{}

		template <typename T> operator T() const
		{
			T t;
			std::stringstream ss;
			return ss << *this && ss >> t ? t : T();
		}

		template <typename T> bool operator==(const T &t) const
		{
			return 0 == this->compare(Variant(t));
		}

		bool operator==(const char *t) const
		{
			return this->compare(t) == 0;
		}

		template <typename T>
		T as()
		{
			return fromString<T>(*this);
		}
};

} // namespace ke

#endif // KE_VARIANT_HPP
