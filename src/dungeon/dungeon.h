#ifndef DUNGEON_H
#define DUNGEON_H

#include <SFML/Graphics.hpp>
#include "../config.h"

class dungeon {
public:
	dungeon();
	~dungeon();

	void update(float deltaTime);
	void draw(sf::RenderWindow& window);

private:
	//	Dungeon settings.
	static const int MAP_HEIGHT = 50, MAP_WIDTH = 75;
	static const int MAX_ROOMS = 4;
	static const int MIN_ROOMS = 2;
	static const int MIN_ROOM_WIDTH = 10, MAX_ROOM_WIDTH = 20;
	static const int MIN_ROOM_HEIGHT = 7, MAX_ROOM_HEIGHT = 20;
	static const int ROOM_BUFFER = 2;
	static const int CORRIDOR_SIZE = 1;

	//	Texture settings.
	static sf::Texture tileTexture;
	//sf::Sprite tileSprites[2];

	//	Method to randomly generate dungeon.
	void generateDungeon();

	//	Methods used to generate different layers of the dungeon.
	void generateRooms();
	void generateWalls();
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
			return sf::IntRect(interior.left - ROOM_BUFFER, interior.top - ROOM_BUFFER,
				interior.width + 2*ROOM_BUFFER, interior.height + 2*ROOM_BUFFER);
		}

		bool intersects(room room2) {
			return bufferBounds().intersects(room2.bufferBounds());
		}
	};

	struct tile {
		enum TileType { FLOOR_T, WALL_T, EMPTY_T };
		TileType type = EMPTY_T;
		bool walkable = false;
		sf::Sprite sprite;
		int x = 0;
		int y = 0;
		tile(int x, int y, sf::IntRect textureRect) {
			this->x = x;
			this->y = y;
			sprite.setTexture(tileTexture);
			sprite.setTextureRect(textureRect);
			sprite.setPosition(x * config::TILE_SIZE,
				y * config::TILE_SIZE + config::TILE_SIZE - sprite.getTextureRect().height);
		}
		tile() {
			sprite.setTexture(tileTexture);
		}

		void draw(sf::RenderWindow& window) {
			if(type != EMPTY_T)
				window.draw(sprite);
		}
	};
	struct wall : tile {
		static const sf::IntRect WALL;
		static const int COLUMNS = 7;
		static const int COUNT = 7;
		wall(int x, int y, int index) : tile(x, y,
			sf::IntRect(WALL.left + WALL.width * (index % COLUMNS),
			WALL.top + WALL.height * (index/COLUMNS), WALL.width, WALL.height)) {
			type = WALL_T;
		}
		wall() : tile(0, 0, WALL) {
			type = WALL_T;
		}
	};
	struct floor : tile {
		static const sf::IntRect FLOOR;
		static const int COLUMNS = 30;
		static const int COUNT = 72;
		floor(int x, int y, int index) : tile(x, y,
			sf::IntRect(FLOOR.left + FLOOR.width * (index % COLUMNS),
			FLOOR.top + FLOOR.height * (index/COLUMNS), FLOOR.width, FLOOR.height)) {
			type = FLOOR_T;
			walkable = true;
		}
		floor() : tile(0, 0, FLOOR) {
			type = FLOOR_T;
			walkable = true;
		}
	};
	struct decoration {};

	void corridor(room room1, room room2);
	void tileRoom(room area);
	void decorateRoom(room area);

	//	TODO: Figure out why I can only use a vector and not an array.
	std::vector<tile> map;
	tile getTile(int x, int y);
};

#endif
