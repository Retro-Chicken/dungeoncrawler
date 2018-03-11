#include "dungeon.h"
#include <iostream>
//using namespace std;

void dungeon::setTile(int x, int y, tile::TileType type) { map[y * dungeon::MAP_WIDTH + x].setType(type); }
dungeon::tile dungeon::getTile(int x, int y) { return map[y * dungeon::MAP_WIDTH + x]; }

dungeon::dungeon() {

	//map.clear();
	//for(int i = 0; i < MAP_WIDTH * MAP_HEIGHT; i++) {
	//	tile temp;
	//	map.push_back(temp);
	//}
	std::cout << map[0].walkable;
	map[0].walkable = true;
	tileTexture.loadFromFile("resources/tilesets/dungeon_tileset.png");
	tileSprites[tile::FLOOR].setTexture(tileTexture);
	tileSprites[tile::FLOOR].setTextureRect(sf::IntRect(16, 96, 16, 16));
	tileSprites[tile::WALL].setTexture(tileTexture);
	tileSprites[tile::WALL].setTextureRect(sf::IntRect(42, 16, 16, 32));
	generateDungeon();
}

dungeon::~dungeon() {

}

void dungeon::update(float deltaTime) {

}

void dungeon::draw(sf::RenderWindow& window) {
	sf::Sprite sprite;
	sprite.setTexture(tileTexture);
	window.draw(sprite);
	for(int x = 0; x < MAP_WIDTH; x++) {
		for(int y = 0; y < MAP_HEIGHT; y++) {
			if(getTile(x, y).type == tile::EMPTY) continue;
			tileSprites[getTile(x, y).type].setPosition(x * config::TILE_SIZE,
			y * config::TILE_SIZE + config::TILE_SIZE -
			tileSprites[getTile(x, y).type].getTextureRect().height);
			window.draw(tileSprites[getTile(x, y).type]);
		}
	}
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
void dungeon::generateDungeon() {
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
				for(int j = y; j < y + h; j++) {
					if(j == y)
						setTile(i, j - 1, tile::WALL);
					setTile(i, j, tile::FLOOR);
				}

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
	for(int x = std::min(x1, x2); x <= std::max(x1, x2); x++) {
		if(getTile(x, y).type == tile::EMPTY) {
			setTile(x, y, tile::FLOOR);
			setTile(x, y - 1, tile::WALL);
		}
	}
}
void dungeon::vCorridor(int y1, int y2, int x) {
	for(int y = std::min(y1, y2); y <= std::max(y1, y2); y++)
		if(getTile(x, y).type == tile::EMPTY)
			setTile(x, y, tile::FLOOR);
}
