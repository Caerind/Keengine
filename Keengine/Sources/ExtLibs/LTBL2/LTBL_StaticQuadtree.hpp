#ifndef LTBL_STATICQUADTREE_HPP
#define LTBL_STATICQUADTREE_HPP

#include <cassert>

#include "LTBL_Quadtree.hpp"

namespace ltbl 
{

class StaticQuadtree : public Quadtree
{
	public:
		StaticQuadtree();

		StaticQuadtree(const sf::FloatRect &rootRegion);

		StaticQuadtree(const StaticQuadtree &other);

		void operator=(const StaticQuadtree &other);

		void create(const sf::FloatRect &rootRegion);

		void add(QuadtreeOccupant* oc); // Inherited from Quadtree

		void clear();

		const sf::FloatRect& getRootRegion() const;

		bool created() const;
	};
}

#endif // LTBL_STATICQUADTREE_HPP
