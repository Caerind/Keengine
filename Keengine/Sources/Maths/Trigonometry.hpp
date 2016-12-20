#ifndef KE_TRIGONOMETRY_HPP
#define KE_TRIGONOMETRY_HPP

#include <cmath>

namespace ke
{

inline float pi()
{ 
	return 3.141592653589793f; 
}

inline float radToDeg(float rad)
{
	float angle = 57.29577951308233f * rad;
	while (angle < 0.f)
	{
		angle += 360.f;
	}
	while (angle > 360.f)
	{
		angle -= 360.f;
	}
	return angle;
}

inline float degToRad(float deg)
{ 
	return 0.01745329251994f * deg; 
}

inline float cos(float deg) 
{ 
	return std::cos(degToRad(deg)); 
}

inline float sin(float deg) 
{ 
	return std::sin(degToRad(deg)); 
}

inline float tan(float deg) 
{ 
	return std::tan(degToRad(deg)); 
}

inline float acos(float value)
{ 
	return radToDeg(std::acos(value)); 
}

inline float asin(float value)
{ 
	return radToDeg(std::asin(value));
}

inline float atan(float value)
{ 
	return radToDeg(std::atan(value)); 
}

inline float atan2(float valY, float valX)
{ 
	return radToDeg(std::atan2(valY, valX)); 
}

} // namespace ke

#endif // KE_TRIGONOMETRY_HPP
