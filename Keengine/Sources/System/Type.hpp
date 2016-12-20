#ifndef KE_TYPE_HPP
#define KE_TYPE_HPP

// Thanks to niXman from http://stackoverflow.com/questions/4976018/compile-time-string-hashing for the string hasing function at compile time

namespace ke
{

namespace priv
{

template<unsigned int N, unsigned int I = 0>
struct hash_calc
{
	static constexpr unsigned int apply(const char(&s)[N])
	{
		return (hash_calc<N, I + 1>::apply(s) ^ s[I]) * 17;
	};
};

template<unsigned int N>
struct hash_calc<N, N>
{
	static constexpr unsigned int apply(const char(&s)[N])
	{
		return 23;
	};
};

} // namespace priv

template<unsigned int N>
constexpr unsigned int hashType(const char(&s)[N])
{
	return priv::hash_calc<N>::apply(s);
}

} // namespace ke

#define TYPE(CLASS_NAME) static const std::string getStaticType() { return #CLASS_NAME; } \
						 static constexpr unsigned int getStaticTypeId() { return ke::hashType(#CLASS_NAME); } \
                         virtual const std::string getType() const { return getStaticType(); } \
					     virtual const unsigned int getTypeId() const { return getStaticTypeId(); }

#endif // KE_TYPE_HPP
