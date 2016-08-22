#include "LTBL_QuadtreeOccupant.hpp"

#include "LTBL_QuadtreeNode.hpp"
#include "LTBL_Quadtree.hpp"

namespace ltbl
{

QuadtreeOccupant::QuadtreeOccupant()
	: _pQuadtreeNode(nullptr), _pQuadtree(nullptr)
{}

void QuadtreeOccupant::quadtreeUpdate()
{
	if (_pQuadtreeNode != nullptr)
		_pQuadtreeNode->update(this);
	else {
		_pQuadtree->_outsideRoot.erase(this);

		_pQuadtree->add(this);
	}
}

void QuadtreeOccupant::quadtreeRemove()
{
	if (_pQuadtreeNode != nullptr)
		_pQuadtreeNode->remove(this);
	else
		_pQuadtree->_outsideRoot.erase(this);
}

} // namespace ltbl