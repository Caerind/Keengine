#ifndef LTBL_DYNAMICQUADTREE_HPP
#define LTBL_DYNAMICQUADTREE_HPP

#include <assert.h>

#include "LTBL_Quadtree.hpp"

namespace ltbl 
{

class DynamicQuadtree : public Quadtree 
{
private:
	void expand();
		
	void contract();

public:
	size_t _minOutsideRoot;
	size_t _maxOutsideRoot;

	DynamicQuadtree();

	DynamicQuadtree(const sf::FloatRect &rootRegion);

	DynamicQuadtree(const DynamicQuadtree &other);

	void operator=(const DynamicQuadtree &other);

	void create(const sf::FloatRect &rootRegion);

	// Inherited from Quadtree
	void add(QuadtreeOccupant* oc);

	void clear();

	// Resizes Quadtree
	void trim();

	bool created() const;

	const sf::FloatRect& getRootRegion() const;
};

} // namespace ltbl

#endif // LTBL_DYNAMICQUADTREE_HPP