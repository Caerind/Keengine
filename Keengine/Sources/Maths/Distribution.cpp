#include "Distribution.hpp"

namespace Distributions
{

Distribution<int> uniform(int min, int max)
{
    return uniformT(min, max);
}

Distribution<unsigned int> uniform(unsigned int min, unsigned int max)
{
    return uniformT(min, max);
}

Distribution<float> uniform(float min, float max)
{
    return uniformT(min, max);
}

Distribution<sf::Time> uniform(sf::Time min, sf::Time max)
{
    assert(min <= max);

    const float floatMin = min.asSeconds();
    const float floatMax = max.asSeconds();

    return Distribution<sf::Time>([=] () -> sf::Time
    {
        return sf::seconds(random(floatMin, floatMax));
    });
}

Distribution<sf::Vector2f> rect(sf::Vector2f center, sf::Vector2f halfSize)
{
    assert(halfSize.x >= 0.f && halfSize.y >= 0.f);
    return Distribution<sf::Vector2f>([=] () -> sf::Vector2f
    {
        return {randomDev(center.x, halfSize.x), randomDev(center.y, halfSize.y)};
    });
}

Distribution<sf::Vector2f> circle(sf::Vector2f center, float radius)
{
    assert(radius >= 0.f);
    return Distribution<sf::Vector2f>([=] () -> sf::Vector2f
    {
        sf::Vector2f n;
        setLength(n, radius * std::sqrt(random(0.f,1.f)));
        setPolarAngle(n, random(0.f,360.f));
        return center + n;
    });
}

Distribution<sf::Vector2f> deflect(sf::Vector2f direction, float maxRotation)
{
    return Distribution<sf::Vector2f>([=] () -> sf::Vector2f
    {
        return direction + rotated(direction, randomDev(0.f,maxRotation));
    });
}

} // namespace Distributions
