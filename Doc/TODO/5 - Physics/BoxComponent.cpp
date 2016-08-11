#include "BoxComponent.hpp"

NBoxComponent::NBoxComponent()
{
    setPointCount(4);
}

void NBoxComponent::setOrigin(sf::Vector2f const& origin)
{
    sf::Vector2f size = getPoint(2) - getPoint(0);
    setPoint(0,origin);
    setPoint(1,origin + sf::Vector2f(size.x, 0.f));
    setPoint(2,origin + size);
    setPoint(3,origin + sf::Vector2f(0.f, size.y));
}

void NBoxComponent::setSize(sf::Vector2f const& size)
{
    sf::Vector2f origin = getPoint(0);
    setPoint(1,origin + sf::Vector2f(size.x,0.f));
    setPoint(2,origin + size);
    setPoint(3,origin + sf::Vector2f(0.f,size.y));
}

void NBoxComponent::setRect(sf::FloatRect const& rect)
{
    setOrigin(sf::Vector2f(rect.left,rect.top));
    setSize(sf::Vector2f(rect.width,rect.height));
}

sf::Vector2f NBoxComponent::getOrigin() const
{
    return mOrigin;
}

sf::Vector2f NBoxComponent::getSize() const
{
    return getPoint(2);
}

sf::FloatRect NBoxComponent::getBox() const
{
    return sf::FloatRect(getOrigin(),getSize());
}

sf::FloatRect NBoxComponent::getFinalBox() const
{
    return getFinalTransform().transformRect(getBox());
}
