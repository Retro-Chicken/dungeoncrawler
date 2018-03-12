#include "dungeon.h"
#include <iostream>

const sf::IntRect dungeon::wall::WALL = sf::IntRect(0, 16, 16, 32);
const sf::IntRect dungeon::floor::FLOOR = sf::IntRect(0, 64, 16, 16);
sf::Texture dungeon::tileTexture;

dungeon::tile dungeon::getTile(int x, int y) { return map[y * dungeon::MAP_WIDTH + x]; }

dungeon::dungeon() {
	for(int i = 0; i < MAP_WIDTH * MAP_HEIGHT; i++) {
		tile temp;
		map.push_back(temp);
	}
	tileTexture.loadFromFile("resources/tilesets/dungeon_tileset.png");
	generateDungeon();
}

dungeon::~dungeon() {

}

void dungeon::update(float deltaTime) {

}

void dungeon::draw(sf::RenderWindow& window) {
	for(int x = 0; x < MAP_WIDTH; x++)
		for(int y = 0; y < MAP_HEIGHT; y++)
			getTile(x, y).draw(window);
}

void dungeon::generateDungeon() {
	generateRooms();
	generateWalls();
	generateDecorations();
}

static const int MAX_ROOM_ATTEMPTS = 100;
struct room {
	sf::IntRect interior;
	sf::Vector2i center;

	room(int x, int y, int w, int h) : interior(x, y, w, h) {
		center.x = interior.left + interior.width/2;
		center.y = interior.top + interior.height/2;
	}

	bool intersects(room room2) {
		return room2.interior.intersects(interior);
	}
};
void dungeon::generateRooms() {
	std::vector<room> rooms;
	int roomCount = rand() % (MAX_ROOMS - MIN_ROOMS) + MIN_ROOMS;
	int attempts = 0;
	while(rooms.size() < roomCount && attempts < MAX_ROOM_ATTEMPTS) {
		int w = rand() % (MAX_ROOM_WIDTH - MIN_ROOM_WIDTH + 1) + MIN_ROOM_WIDTH;
		int h = rand() % (MAX_ROOM_HEIGHT - MIN_ROOM_HEIGHT) + MIN_ROOM_HEIGHT;
		int x = rand() % (MAP_WIDTH - w);
		int y = rand() % (MAP_HEIGHT - h - 1) + 1;
		room curRoom(x, y, w, h);

		bool failed = false;
		for(int i = 0; i < rooms.size(); i++)
			if(rooms[i].intersects(curRoom)) {
				failed = true;
				break;
			}

		if(!failed) {
			for(int i = x; i < x + w; i++)
				for(int j = y; j < y + h; j++)
					map.at(j * MAP_WIDTH + i) = dungeon::floor(i, j, 0);

			if(rooms.size() > 0) {
				hCorridor(rooms[rooms.size() - 1].center.x, curRoom.center.x, curRoom.center.y);
				vCorridor(rooms[rooms.size() - 1].center.y, curRoom.center.y, rooms[rooms.size() - 1].center.x);
			}

			rooms.push_back(curRoom);
			attempts = 0;
		} else
			attempts++;
	}
}
void dungeon::hCorridor(int x1, int x2, int y) {
	for(int x = std::min(x1, x2); x <= std::max(x1, x2); x++)
		for(int i = 0; i < CORRIDOR_SIZE; i++)
			map.at((y - CORRIDOR_SIZE/2 + i) * MAP_WIDTH + x) =
				dungeon::floor(x, y - CORRIDOR_SIZE/2 + i, 0);
}
void dungeon::vCorridor(int y1, int y2, int x) {
	for(int y = std::min(y1, y2); y <= std::max(y1, y2); y++)
		for(int i = 0; i < CORRIDOR_SIZE; i++)
			map.at(y * MAP_WIDTH + x - CORRIDOR_SIZE/2 + i) =
				dungeon::floor(x - CORRIDOR_SIZE/2 + i, y, 0);
}

void dungeon::generateWalls() {
	for(int x = 0; x < MAP_WIDTH; x++)
		for(int y = 0; y < MAP_HEIGHT - 1; y++)
			if(getTile(x, y).type == tile::EMPTY_T &&
				getTile(x, y + 1).type == tile::FLOOR_T)
				map.at(y * MAP_WIDTH + x) = wall(x, y, 0);
}

void dungeon::generateDecorations() {

}
