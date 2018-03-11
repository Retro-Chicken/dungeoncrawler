#ifndef DUNGEON_H
#define DUNGEON_H

#include <SFML/Graphics.hpp>
#include "../config.h"

class dungeon {
public:

	struct decoration {};

	dungeon();
	~dungeon();

	void update(float deltaTime);
	void draw(sf::RenderWindow& window);

	//tile getTile(int x, int y); { return map[y * MAP_HEIGHT + x]; }

private:
	//	Dungeon settings.
	static const int MAP_HEIGHT = 50, MAP_WIDTH = 75;
	static const int MAX_ROOMS = 4;
	static const int MIN_ROOMS = 2;
	static const int MIN_ROOM_WIDTH = 10, MAX_ROOM_WIDTH = 20;
	static const int MIN_ROOM_HEIGHT = 7, MAX_ROOM_HEIGHT = 20;

	//	Texture settings.
	sf::Texture tileTexture;
	sf::Sprite tileSprites[2];

	void generateDungeon();
	void hCorridor(int x1, int x2, int y);
	void vCorridor(int y1, int y2, int x);

	struct tile {
		//	Can the player walk on the tile?
		bool walkable = false;
		enum TileType { FLOOR = 0, WALL = 1, EMPTY = 2};
		void setType(TileType newType) { type = newType; }
		TileType type = EMPTY;
	};

	tile map[MAP_WIDTH * MAP_HEIGHT];
	void setTile(int x, int y, tile::TileType type);
	tile getTile(int x, int y);
};

#endif
