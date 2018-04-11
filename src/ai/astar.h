#ifndef ASTAR_H
#define ASTAR_H

#include <SFML/Graphics.hpp>
#include "path.h"
#include "../dungeon/dungeonparams.h"
#include <functional>
#include <queue>

class astar {
public:
	static path aStar(const sf::Vector2i& start, const sf::Vector2i& end, std::function<bool(int, int)> isBlocked);

private:
	static const int n = params::MAP_WIDTH; // Horizontal size of the map
	static const int m = params::MAP_HEIGHT; // Vertical size size of the map
	static const int dir = 4; // Number of possible directions to go at any position

	static int dx[dir];
	static int dy[dir];

	astar() {};
};

#endif
