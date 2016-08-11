#ifndef NCOLLISIONCOMPONENT_HPP
#define NCOLLISIONCOMPONENT_HPP

#include "Component.hpp"

class NCollisionComponent : public NComponent
{
    public:
        NCollisionComponent();

        void setPoint(std::size_t index, sf::Vector2f const& position);
        sf::Vector2f getPoint(std::size_t index) const;

        void setPointCount(std::size_t index);
        std::size_t getPointCount() const;

        bool contains(sf::Vector2f const& point);
        bool intersect(NCollisionComponent* component);

    protected:
        std::vector<sf::Vector2f> mPoints;
};

#endif // NCOLLISIONCOMPONENT_HPP
