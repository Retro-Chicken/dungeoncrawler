#ifndef PATH_H
#define PATH_H

#include <SFML/Graphics.hpp>

class path {
public:
	path();
	~path();

	void push_back(sf::Vector2i point) { points.push_back(point); }
	void push(sf::Vector2i point) { points.insert(point); }

	std::vector<sf::Vector2i> points;
};

#endif
