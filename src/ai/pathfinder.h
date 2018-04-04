#ifndef PATH_FINDER_H
#define PATH_FINDER_H

#include <SFML/Graphics.hpp>
#include "path.h"
#include <climits>
#include <set>
#include <functional>

namespace pathfinder {
	path aStar(sf::Vector2i start, sf::Vector2i end, std::function<bool(sf::Vector2i)> isBlocked);
};

#endif
