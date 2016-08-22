#ifndef KE_PATHFINDING_HPP
#define KE_PATHFINDING_HPP

#include <vector>
#include <SFML/System/Vector2.hpp>
#include "Map.hpp"

namespace ke
{

namespace priv
{
	struct Node
	{
		Node(sf::Vector2i c, sf::Vector2i p) { coords = c; parent = p; }
		sf::Vector2i coords;
		sf::Vector2i parent;
	};

	std::vector<sf::Vector2i> reorganizedNeighboors(sf::Vector2i const& pos, sf::Vector2i const& end);

} // namespace priv

std::vector<sf::Vector2i> pathfinding(sf::Vector2i const& begin, sf::Vector2i const& end, std::function<bool(sf::Vector2i const& coords)> collisions);

} // namespace ke

#endif // KE_PATHFINDING_HPP