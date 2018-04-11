#ifndef DUNGEON_H
#define DUNGEON_H

#include <SFML/Graphics.hpp>
#include "../config.h"
#include "../rendertools/drawable.h"
#include "../rendertools/animation.h"
#include "dungeonparams.h"
#include "tools.h"
#include "tile.h"

class dungeon {
public:
	dungeon();
	~dungeon();

	void update(float deltaTime);
	void draw(sf::RenderWindow& window);

	sf::Vector2i getStart();

private:
	//	Method to randomly generate dungeon.
	void generateDungeon();

	//	Methods used to generate different layers of the dungeon.
	void generateRooms();
	void generateWalls();
	void generateDecorations();
	//	Methods to connect two rooms of the dungeon.
	void hCorridor(int x1, int x2, int y);
	void vCorridor(int y1, int y2, int x);

	struct room {
		sf::IntRect interior;
		sf::Vector2i center;

		room(int x, int y, int w, int h) : interior(x, y, w, h) {
			center.x = interior.left + interior.width/2;
			center.y = interior.top + interior.height/2;
		}
		sf::IntRect bufferBounds() {
			return sf::IntRect(interior.left - params::ROOM_BUFFER, interior.top - params::ROOM_BUFFER,
				interior.width + 2*params::ROOM_BUFFER, interior.height + 2*params::ROOM_BUFFER);
		}

		bool intersects(room room2) {
			return bufferBounds().intersects(room2.bufferBounds());
		}
	};

	void corridor(room room1, room room2);
	void tileRoom(room area);
	void decorateRoom(room area);

	//	TODO: Figure out why I can only use a vector and not an array.
	std::vector<tile> map;
public:
	tile& getTile(int x, int y);
	bool isWalkable(sf::Vector2i point) {
		if(point.x >= 0 && point.x < params::MAP_WIDTH && point.y >= 0 && point.y < params::MAP_HEIGHT)
			return getTile(point.x, point.y).walkable;
		return false;
	}
	static sf::Vector2i globalToLocal(sf::Vector2i mouseCoords) {
		return sf::Vector2i(mouseCoords.x / config::TILE_SIZE, mouseCoords.y / config::TILE_SIZE);
	}
	static sf::Vector2i globalToLocal(sf::Vector2f mouseCoords) {
		return sf::Vector2i(((int)mouseCoords.x) / config::TILE_SIZE, ((int)mouseCoords.y) / config::TILE_SIZE);
	}
};

#endif
