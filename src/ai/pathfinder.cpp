#include "pathfinder.h"
#include <climits>

path pathfinder::aStar(sf::Vector2i start, sf::Vector2i end, std::function<bool(sf::Vector2i)> isBlocked) {
	std::vector<sf::Vector2i> closedSet;
	std::vector<sf::Vector2i> openSet;
	openSet.insert(start);

	std::map<sf::Vector2i, sf::Vector2i> cameFrom;

	std::map<sf::Vector2i, int> gScore;
	gScore.insert({start, 0});
	std::map<sf::Vector2i, int> fScore;
	fScore.insert({start, heuristicEstimate(start, end)});

	while(!openSet.empty()) {
		sf::Vector2i current = openSet.at(0);
		for(sf::Vector2i val : openSet)
			if(fScore[val] < fScore[current])
				current = val;
		if(current == end)
			return reconstructPath(cameFrom, current);

		openSet.remove(current);
		closedSet.insert(current);

		for(int i = 0; i < 4; i++) {
			sf::Vector2i neighbor(current);
			switch(i) {
				case 0: neighbor.x -= 1; break;
				case 1: neighbor.x += 1; break;
				case 2: neighbor.y -= 1; break;
				case 3: neighbor.y += 1; break;
			}
			if(closedSet.find(current) != closedSet.end())
				continue;
			if(openSet.find(current) == openSet.end())
				openSet.insert(neighbor);
			tentativeGScore = gScore[current] + 1;
			if(tentativeGScore >= (gScore.find(neighbor) != gScore.end() ? gScore[neighbor] : INT_MAX))
				continue;
			cameFrom.insert({neighbor, current});
			gScore.insert({neighbor, tentativeGScore});
			fScore.insert({neighbor, tentativeGScore + heuristicEstimate(neighbor, end)});
		}
	}
	return NULL;
}

path reconstructPath(std::map<sf::Vector2i, sf::Vector2i> cameFrom, sf::Vector2i current) {
	path result;
	result.push(current);
	while(cameFrom.find(current) != cameFrom.end()) {
		current = cameFrom[current];
		result.push(current);
	}
	return result;
}

int heuristicEstimate(sf::Vector2i current, sf::Vector2i end) {
	return std::abs(current.x - end.x) + std::abs(current.y - end.y);
}
