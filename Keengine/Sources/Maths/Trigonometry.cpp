#include "Trigonometry.hpp"

namespace ne
{

	float pi() { return 3.141592653589793238462643383f; }
	float radToDeg(float rad) { return 180.f / pi() * rad; }
	float degToRad(float deg) { return pi() / 180.f * deg; }
	float cos(float deg) { return std::cos(degToRad(deg)); }
	float sin(float deg) { return std::sin(degToRad(deg)); }
	float tan(float deg) { return std::tan(degToRad(deg)); }
	float acos(float value) { return radToDeg(std::acos(value)); }
	float asin(float value) { return radToDeg(std::asin(value)); }
	float atan(float value) { return radToDeg(std::atan(value)); }
	float atan2(float valY, float valX) { return radToDeg(std::atan2(valY, valX)); }

} // namespace ne
