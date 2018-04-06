#include "path.h"

path::path() {

}

path::~path() {

}

std::string path::toString() {
	std::string result = "";
	for(sf::Vector2i point : points)
		result += "(" + std::to_string(point.x) + ", " + std::to_string(point.y) + ") ";
	return result;
}
