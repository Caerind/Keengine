#ifndef LIGHTSHAPE_HPP
#define LIGHTSHAPE_HPP

#include <memory>

#include "LTBL_QuadtreeOccupant.hpp"

namespace ltbl 
{
	
class LightShape : public QuadtreeOccupant 
{
	public:
		typedef std::shared_ptr<LightShape> Ptr;

		bool _renderLightOverShape;

		sf::ConvexShape _shape;

		LightShape()
			: _renderLightOverShape(true)
		{}

		sf::FloatRect getAABB() const {
			return _shape.getGlobalBounds();
		}
};

} // namespace ltbl

#endif // LIGHTSHAPE_HPP