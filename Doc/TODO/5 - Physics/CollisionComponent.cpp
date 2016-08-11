#include "CollisionComponent.hpp"

NCollisionComponent::NCollisionComponent()
{
}

void NCollisionComponent::setPoint(std::size_t index, sf::Vector2f const& position)
{
    if (0 <= index && index < mPoints.size())
    {
        mPoints[index] = position;
    }
}

sf::Vector2f NCollisionComponent::getPoint(std::size_t index) const
{
    if (0 <= index && index < mPoints.size())
    {
        return mPoints.at(index);
    }
    return sf::Vector2f();
}

void NCollisionComponent::setPointCount(std::size_t index)
{
    mPoints.resize(index);
}

std::size_t NCollisionComponent::getPointCount() const
{
    return mPoints.size();
}

bool NCollisionComponent::contains(sf::Vector2f const& point)
{
    sf::Vector2f p = point - getFinalPosition();
    for (std::size_t i = 0; i < mPoints.size(); i++)
    {
        sf::Vector2f a = getPoint(i);
        sf::Vector2f b = (i == getPointCount() - 1) ? getPoint(0) - a : getPoint(i + 1) - a;
        if (b.x * (p.y - a.y) - b.y * (p.x - a.x) < 0)
        {
            return false;
        }
    }
    return true;
}

bool NCollisionComponent::intersect(NCollisionComponent* component)
{
    if (component == nullptr)
    {
        return false;
    }

    for (std::size_t i = 0; i < mPoints.size(); i++)
    {
        if (component->contains(getPoint(i) + getFinalPosition()))
        {
            return true;
        }
    }
    for (std::size_t i = 0; i < component->getPointCount(); i++)
    {
        if (contains(component->getPoint(i) + component->getFinalPosition()))
        {
            return true;
        }
    }
    return false;
}

