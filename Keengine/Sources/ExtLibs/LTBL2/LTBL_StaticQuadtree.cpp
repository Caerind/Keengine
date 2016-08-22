#include "LTBL_StaticQuadtree.hpp"

namespace ltbl
{

StaticQuadtree::StaticQuadtree()
{
}

StaticQuadtree::StaticQuadtree(const sf::FloatRect & rootRegion)
{
	_pRootNode.reset(new QuadtreeNode(rootRegion, 0, nullptr, this));
}

StaticQuadtree::StaticQuadtree(const StaticQuadtree & other) : Quadtree(other)
{
	*this = other;
}

void StaticQuadtree::operator=(const StaticQuadtree & other)
{
	Quadtree::operator=(other);
}

void StaticQuadtree::create(const sf::FloatRect & rootRegion)
{
	_pRootNode.reset(new QuadtreeNode(rootRegion, 0, nullptr, this));
}

void StaticQuadtree::add(QuadtreeOccupant * oc)
{
	assert(created());
	setQuadtree(oc);
	// If the occupant fits in the root node
	if (rectContains(_pRootNode->getRegion(), oc->getAABB()))
		_pRootNode->add(oc);
	else
		_outsideRoot.insert(oc);
}

void StaticQuadtree::clear()
{
	_pRootNode.reset();
}

const sf::FloatRect& StaticQuadtree::getRootRegion() const
{
	return _pRootNode->getRegion();
}

bool StaticQuadtree::created() const
{
	return _pRootNode != nullptr;
}

} // namespace ltbl