#ifndef TRIGONOMETRY_HPP
#define TRIGONOMETRY_HPP

#include <cmath>

namespace ne
{

	float pi();
	float radToDeg(float rad);
	float degToRad(float deg);
	float cos(float deg);
	float sin(float deg);
	float tan(float deg);
	float acos(float value);
	float asin(float value);
	float atan(float value);
	float atan2(float valY, float valX);

} // namespace ne

#endif // TRIGONOMETRY_HPP
