#include "Pathfinding.hpp"

namespace ke
{

namespace priv
{
	std::vector<sf::Vector2i> reorganizedNeighboors(sf::Vector2i const& pos, sf::Vector2i const& end)
	{
		std::vector<sf::Vector2i> p;
		/*
		std::vector<sf::Vector2i> n = Map::getNeighboors(pos, false);
		sf::Vector2f delta = coordsToWorld(end) - coordsToWorld(pos);
		if (delta != sf::Vector2f())
		{
			return n;
		}
		float angle = getPolarAngle(delta);
		if (0.f <= angle && angle < 30.f) // 2130
		{
			p.push_back(n.at(2));
			p.push_back(n.at(1));
			p.push_back(n.at(3));
			p.push_back(n.at(0));
		}
		else if (30.f <= angle && angle < 90.f) // 2310
		{
			p.push_back(n.at(2));
			p.push_back(n.at(3));
			p.push_back(n.at(1));
			p.push_back(n.at(0));
		}
		else if (90.f <= angle && angle < 150.f) // 3201
		{
			p.push_back(n.at(3));
			p.push_back(n.at(2));
			p.push_back(n.at(0));
			p.push_back(n.at(1));
		}
		else if (150.f <= angle && angle < 180.f) // 3021
		{
			p.push_back(n.at(3));
			p.push_back(n.at(0));
			p.push_back(n.at(2));
			p.push_back(n.at(1));
		}
		else if (180.f <= angle && angle < 210.f) // 0312
		{
			p.push_back(n.at(0));
			p.push_back(n.at(3));
			p.push_back(n.at(1));
			p.push_back(n.at(2));
		}
		else if (210.f <= angle && angle < 270.f) // 0132
		{
			p.push_back(n.at(0));
			p.push_back(n.at(1));
			p.push_back(n.at(3));
			p.push_back(n.at(2));
		}
		else if (270.f <= angle && angle < 330.f) // 1023
		{
			p.push_back(n.at(1));
			p.push_back(n.at(0));
			p.push_back(n.at(2));
			p.push_back(n.at(3));
		}
		else // 1203
		{
			p.push_back(n.at(1));
			p.push_back(n.at(2));
			p.push_back(n.at(0));
			p.push_back(n.at(3));
		}
		*/
		return p;
	}
}

std::vector<sf::Vector2i> pathfinding(sf::Vector2i const & begin, sf::Vector2i const & end, std::function<bool(sf::Vector2i const&coords)> collisions)
{
	std::vector<priv::Node> container;
	if (begin == end)
	{
		return{};
	}
	container.push_back(priv::Node(begin, begin));
	std::size_t test = 0;
	bool reached = false;
	std::vector<priv::Node> temp;
	while (test < 30 && !reached)
	{
		for (std::size_t i = 0; i < container.size(); i++)
		{
			std::vector<sf::Vector2i> n = priv::reorganizedNeighboors(container[i].coords, end);
			for (std::size_t j = 0; j < n.size(); j++)
			{
				bool addToList = true;
				if (collisions)
				{
					if (collisions(n[j]))
					{
						addToList = false;
					}
				}
				for (std::size_t k = 0; k < container.size(); k++)
				{
					if (container[k].coords == n[j])
					{
						addToList = false;
					}
				}
				for (std::size_t k = 0; k < temp.size(); k++)
				{
					if (temp[k].coords == n[j])
					{
						addToList = false;
					}
				}
				if (addToList)
				{
					temp.push_back(priv::Node(n[j], container[i].coords));
					if (n[j] == end)
					{
						reached = true;
					}
				}
			}
		}
		for (std::size_t i = 0; i < temp.size(); i++)
		{
			container.push_back(temp[i]);
		}
		temp.clear();
		test++;
	}

	std::vector<sf::Vector2i> path;
	if (reached)
	{
		sf::Vector2i pos = end;
		reached = false;
		while (!reached)
		{
			bool handled = false;
			for (std::size_t i = 0; i < container.size(); i++)
			{
				if (container[i].coords == pos && !handled)
				{
					path.push_back(pos);
					if (container[i].parent == container[i].coords)
					{
						reached = true;
					}
					pos = container[i].parent;
					handled = true;
				}
			}
		}
		path.pop_back();
		std::reverse(path.begin(), path.end());
	}
	return path;
}

} // namespace ke
