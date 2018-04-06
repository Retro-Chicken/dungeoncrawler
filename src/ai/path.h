#ifndef PATH_H
#define PATH_H

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class path {
public:
	path();
	~path();

	void push_back(sf::Vector2i point) { points.push_back(point); }
	void push(sf::Vector2i point) { points.insert(points.begin(), point); }

	std::vector<sf::Vector2i> points;

	std::string toString();
};

#endif
