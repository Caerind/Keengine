#include "Vector2.hpp"

float distance(sf::Vector2f const& l, sf::Vector2f const& r)
{
    return getLength(l-r);
}

bool isZero(sf::Vector2f const& vector)
{
    return (vector.x == 0.f && vector.y == 0.f);
}

sf::Vector2f polarVector(float length, float angle)
{
    return sf::Vector2f(length * cos(angle), length * sin(angle));
}

float getLength(sf::Vector2f const& vector)
{
    return std::sqrt(getSquaredLength(vector));
}

float getSquaredLength(sf::Vector2f const& vector)
{
    return dotProduct(vector, vector);
}

void setLength(sf::Vector2f& vector, float length)
{
    assert(!isZero(vector));
    vector *= length / getLength(vector);
}

bool isNormalized(sf::Vector2f const& vector)
{
    return (getSquaredLength(vector) == 1.f);
}

void normalize(sf::Vector2f& vector)
{
    setLength(vector, 1.f);
}

sf::Vector2f normalized(sf::Vector2f const& vector)
{
    assert(!isZero(vector));
	return vector / getLength(vector);
}

sf::Vector2f normalized(float angle)
{
    return sf::Vector2f(cos(angle), sin(angle));
}

float getPolarAngle(sf::Vector2f const& vector)
{
    assert(!isZero(vector));
    return atan2(vector.y, vector.x);
}

void setPolarAngle(sf::Vector2f& vector, float angle)
{
    float length = getLength(vector);
    vector.x = length * cos(angle);
    vector.y = length * sin(angle);
}

void rotate(sf::Vector2f& vector, float angle)
{
    float c = cos(angle);
	float s = sin(angle);
    vector = sf::Vector2f(c * vector.x - s * vector.y, s * vector.x + c * vector.y);
}

sf::Vector2f rotated(sf::Vector2f const& vector, float angle)
{
    float c = cos(angle);
	float s = sin(angle);
    return sf::Vector2f(c * vector.x - s * vector.y, s * vector.x + c * vector.y);
}

float dotProduct(sf::Vector2f const& l, sf::Vector2f const& r)
{
    return l.x * r.x + l.y * r.y;
}

float crossProduct(sf::Vector2f const& l, sf::Vector2f const& r)
{
    return l.x * r.y - l.y * r.x;
}

sf::Vector2f cwiseProduct(sf::Vector2f const& l, sf::Vector2f const& r)
{
	return sf::Vector2f(l.x * r.x, l.y * r.y);
}

sf::Vector2f cwiseQuotient(sf::Vector2f const& l, sf::Vector2f const& r)
{
	assert(!isZero(r));
	return sf::Vector2f(l.x / r.x, l.y / r.y);
}

sf::Vector2f projectedVector(sf::Vector2f const& vector, sf::Vector2f const& axis)
{
	assert(!isZero(axis));
	return dotProduct(vector, axis) / getSquaredLength(axis) * axis;
}

sf::Vector3f toVector3f(sf::Vector2f const& vector)
{
    return sf::Vector3f(vector.x, vector.y, 0.f);
}

std::string toString(sf::Vector2f const& vector)
{
    std::ostringstream oss;
    oss << vector.x << "," << vector.y;
    return oss.str();
}

sf::Vector2f toVector2f(std::string const& str)
{
    sf::Vector2f vector;
    std::size_t found = str.find_first_of(',');
    if (found != std::string::npos)
    {
        std::istringstream iss(str.substr(0, found));
        iss >> vector.x;
        iss.clear();
        iss.str(str.substr(found + 1));
        iss >> vector.y;
    }
    return vector;
}

sf::Vector2f lerp(sf::Vector2f const& start, sf::Vector2f const& end, float percent)
{
    return (start + percent * (end - start));
}

sf::Vector2f slerp(sf::Vector2f const& start, sf::Vector2f const& end, float percent)
{
    if (percent == 0.f)
    {
        return start;
    }
    if (start == end || percent == 1.0f)
    {
        return end;
    }
    float theta = acos(dotProduct(start, end) / (getLength(start) * getLength(end)));
    if (theta == 0.f)
    {
        return end;
    }
    float sinTheta = sin(theta);
    return (start * (sin((1 - percent) * theta) / sinTheta)) + (end * (sin(percent * theta) / sinTheta));
}

sf::Vector2f nlerp(sf::Vector2f const& start, sf::Vector2f const& end, float percent)
{
    return normalized(lerp(start,end,percent));
}
