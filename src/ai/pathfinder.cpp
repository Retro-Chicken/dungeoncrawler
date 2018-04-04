#include "pathfinder.h"

int heuristicEstimate(sf::Vector2i current, sf::Vector2i end);
struct SearchPoint {
	sf::Vector2i point;
	int gValue = INT_MAX/2;
	int hValue = INT_MAX/2;

	SearchPoint() {}

	SearchPoint(sf::Vector2i point, sf::Vector2i end) {
		this->point = point;
		hValue = heuristicEstimate(point, end);
	}
	bool operator== (const SearchPoint& right) const {
		return point == right.point;
	}

	int getFValue() const { return gValue + hValue; }

	bool operator<(const SearchPoint& right) const {
		return getFValue() < right.getFValue();
	}
};

path reconstructPath(std::map<SearchPoint, SearchPoint> cameFrom, SearchPoint current);

path pathfinder::aStar(sf::Vector2i start, sf::Vector2i end, std::function<bool(sf::Vector2i)> isBlocked) {
	std::set<SearchPoint> closedSet;
	std::set<SearchPoint> openSet;
	SearchPoint startSP(start, end);
	SearchPoint endSP(end, end);
	startSP.gValue = 0;
	openSet.insert(startSP);

	std::map<SearchPoint, SearchPoint> cameFrom;

	std::set<SearchPoint> gScores;
	gScores.insert(startSP);

	while(!openSet.empty()) {
		SearchPoint current = *(openSet.begin());
		if(current == endSP)
			return reconstructPath(cameFrom, current);

		openSet.erase(openSet.begin());
		closedSet.insert(current);

		for(int i = 0; i < 4; i++) {
			SearchPoint neighbor(current.point, end);
			switch(i) {
				case 0: neighbor.point.x -= 1; break;
				case 1: neighbor.point.x += 1; break;
				case 2: neighbor.point.y -= 1; break;
				case 3: neighbor.point.y += 1; break;
			}
			if(isBlocked(neighbor.point))
				continue;
			if(closedSet.find(neighbor) != closedSet.end())
				continue;
			if(openSet.find(neighbor) == openSet.end())
				openSet.insert(neighbor);
			int tentativeGScore = current.gValue + 1;
			if(tentativeGScore >= (gScores.find(neighbor) != gScores.end() ? gScores.find(neighbor)->gValue : INT_MAX))
				continue;
			cameFrom.insert({neighbor, current});
			neighbor.gValue = tentativeGScore;
			gScores.insert(neighbor);
		}
	}
	return path();
}

path reconstructPath(std::map<SearchPoint, SearchPoint> cameFrom, SearchPoint current) {
	path result;
	result.push(current.point);
	while(cameFrom.find(current) != cameFrom.end()) {
		current = cameFrom[current];
		result.push(current.point);
	}
	return result;
}

int heuristicEstimate(sf::Vector2i current, sf::Vector2i end) {
	return std::abs(current.x - end.x) + std::abs(current.y - end.y);
}
