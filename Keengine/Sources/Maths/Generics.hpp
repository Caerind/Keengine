#ifndef KE_GENERICS_HPP
#define KE_GENERICS_HPP

#include <algorithm>
#include <sstream>

namespace ke
{

template <typename T>
inline T clamp(T& value, const T& min, const T& max)
{
    value = std::max(min, std::min(value, max));
}

template <typename T>
inline T abs(const T& value)
{
    return std::abs(value);
}

template <typename T>
inline T sqrt(const T& value)
{
    return std::sqrt(value);
}

template <typename T>
inline std::string decToHex(const T& decimal)
{
    std::ostringstream oss;
    oss << std::hex << decimal;
    return oss.str();
}

template <typename T>
inline T hexToDec(const std::string& hexadecimal)
{
    std::istringstream iss(hexadecimal);
    T decimal;
    iss >> std::hex >> decimal;
    return decimal;
}

template <typename T>
inline std::string decToOct(const T& decimal)
{
    std::ostringstream oss;
    oss << std::oct << decimal;
    return oss.str();
}

template <typename T>
inline T octToDec(const std::string& octal)
{
    std::istringstream iss(octal);
    T decimal;
    iss >> std::oct >> decimal;
    return decimal;
}

template <typename T>
inline std::string decToBin(const T& decimal)
{
    std::vector<bool> values;
    while (decimal > 0)
    {
        values.push_back(((decimal % 2) == 1));
        decimal /= 2;
    }
    std::string r;
    for (std::size_t i = 0; i < values.size(); i++)
    {
        r += (values[i] == true) ? "1" : "0";
    }
    std::reverse(r.begin(), r.end());
    return r;
}

template <typename T>
inline T binToDec(const std::string& binary)
{
    T decimal = 0, factor = 1;
    std::string temp = binary;
    std::reverse(temp.begin(), temp.end());
    for (std::size_t i = 0; i < temp.size(); i++)
    {
        decimal += factor * ((temp[i] == '1') ? 1 : 0);
        factor *= 2;
    }
    return decimal;
}

class Average
{
	public:
		Average() : mAverage(0.f), mCount(0) {}

		float add(float term) 
		{ 
			mAverage = ((mAverage * mCount) + term) * 1.f / (mCount + 1);
			mCount++;
			return mAverage;
		}

		float get() { return mAverage; }

		std::size_t getCount() { return mCount; }

	private:
		float mAverage;
		std::size_t mCount;
};

} // namespace ke

#endif // KE_GENERICS_HPP
