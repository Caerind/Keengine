#ifndef LTBL_QUADTREENODE_HPP
#define LTBL_QUADTREENODE_HPP

#include "LTBL_QuadtreeOccupant.hpp"

#include <memory>
#include <array>
#include <unordered_set>

namespace ltbl 
{
	
class QuadtreeNode : public sf::NonCopyable 
{
	private:
		QuadtreeNode* _pParent;
		class Quadtree* _pQuadtree;

		bool _hasChildren;

		std::array<std::unique_ptr<QuadtreeNode>, 4> _children;

		std::unordered_set<QuadtreeOccupant*> _occupants;

		sf::FloatRect _region;

		unsigned _level;

		unsigned _numOccupantsBelow;

		void getPossibleOccupantPosition(QuadtreeOccupant* oc, sf::Vector2i &point);

		void addToThisLevel(QuadtreeOccupant* oc);

		// Returns true if occupant was added to children
		bool addToChildren(QuadtreeOccupant* oc);

		void destroyChildren();

		void getOccupants(std::unordered_set<QuadtreeOccupant*> &occupants);

		void partition();

		void merge();

		void update(QuadtreeOccupant* oc);
		
		void remove(QuadtreeOccupant* oc);

		void removeForDeletion(std::unordered_set<QuadtreeOccupant*> &occupants);

	public:
		QuadtreeNode();

		QuadtreeNode(const sf::FloatRect &region, int level, QuadtreeNode* pParent, class Quadtree* pQuadtree);

		// For use after using default constructor
		void create(const sf::FloatRect &region, int level, QuadtreeNode* pParent, class Quadtree* pQuadtree);

		class Quadtree* getTree() const;

		void add(QuadtreeOccupant* oc);

		const sf::FloatRect& getRegion() const;

		void getAllOccupantsBelow(std::vector<QuadtreeOccupant*> &occupants);

		void getAllOccupantsBelow(std::unordered_set<QuadtreeOccupant*> &occupants);

		int getNumOccupantsBelow() const;

		void pruneDeadReferences();

		friend class QuadtreeOccupant;
		friend class Quadtree;
		friend class DynamicQuadtree;
};

} // namespace ltbl

#endif // LTBL_QUADTREENODE_HPP