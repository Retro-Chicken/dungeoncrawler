#include "path.h"

path::path() {

}

path::~path() {

}

sf::Vector2i path::pop() {
	if(!points.empty()) {
		sf::Vector2i topElement = top();
		points.erase(points.begin());
		return topElement;
	} else
		return sf::Vector2i(-1, -1);
}

sf::Vector2i path::top() {
	if(!points.empty())
		return points[0];
	else
		return sf::Vector2i(-1, -1);
}

std::string path::toString() {
	std::string result = "";
	for(sf::Vector2i point : points)
		result += "(" + std::to_string(point.x) + ", " + std::to_string(point.y) + ") ";
	return result;
}
