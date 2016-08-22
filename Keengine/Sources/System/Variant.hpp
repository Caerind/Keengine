#ifndef KE_VARIANT_HPP
#define KE_VARIANT_HPP

#include <sstream>

namespace ke
{

class Variant : public std::string
{
	public:
		template <typename T>
		Variant(const T &t) : std::string(std::to_string(t))
		{}

		Variant(bool boolean) : std::string((boolean) ? "true" : "false")
		{}

		template <size_t N>
		Variant(const char(&s)[N]) : std::string(s, N)
		{}

		Variant(const char *cstr) : std::string(cstr)
		{}

		Variant(const std::string &other = std::string()) : std::string(other)
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

		inline bool asBool()
		{
			return (*this == "true");
		}

		inline int asInt()
		{
			std::stringstream iss(*this);
			int value;
			iss >> value;
			return value;
		}

		inline unsigned int asUint()
		{
			std::stringstream iss(*this);
			unsigned int value;
			iss >> value;
			return value;
		}

		inline float asFloat()
		{
			std::stringstream iss(*this);
			float value;
			iss >> value;
			return value;
		}
};

} // namespace ke

#endif // KE_VARIANT_HPP
