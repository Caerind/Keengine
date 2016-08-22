#ifndef LTBL_QUADTREEOCCUPANT_HPP
#define LTBL_QUADTREEOCCUPANT_HPP

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "LTBL_Math.hpp"

#include <memory>
#include <array>
#include <unordered_set>

namespace ltbl 
{

class QuadtreeOccupant 
{
	private:
		class QuadtreeNode* _pQuadtreeNode;
		class Quadtree* _pQuadtree;

	public:
		QuadtreeOccupant();

		void quadtreeUpdate();
		
		void quadtreeRemove();

		virtual sf::FloatRect getAABB() const = 0;

		friend class Quadtree;
		friend class QuadtreeNode;
		friend class DynamicQuadtree;
		friend class StaticQuadtree;
};

} // namespace ltbl

#endif // LTBL_QUADTREEOCCUPANT_HPP