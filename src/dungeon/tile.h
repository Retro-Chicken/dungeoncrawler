#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>
#include <set>
#include "../rendertools/drawable.h"

class tile {
public:
	tile(int x, int y);
	~tile();

	int x = 0;
	int y = 0;

	bool walkable = false;
	void setWalkable(bool walkable) { this->walkable = walkable; }

	struct drawablecompare {
		bool operator()(const drawable* lhs, const drawable* rhs) const  { return *lhs < *rhs; }
	};
	std::set<drawable*, drawablecompare> graphics;

	bool isEmpty() { return graphics.size() == 0; }
	void clear();
	void addDrawable(drawable* item);
	void forceDrawable(drawable* item);

	void update(float deltaTime);
	void draw(sf::RenderWindow& window) const;

	std::string getTag() { return graphics.size() > 0 ? (*graphics.begin())->tag : ""; }
};

#endif
