#include "dungeon.h"
#include <iostream>

const sf::IntRect dungeon::wall::WALL = sf::IntRect(0, 16, 16, 32);
const sf::IntRect dungeon::floor::FLOOR = sf::IntRect(0, 64, 16, 16);
const sf::IntRect dungeon::banner::BANNER = sf::IntRect(288, 128, 16, 32);
sf::Texture dungeon::tileTexture;

dungeon::tile dungeon::getTile(int x, int y) { return map[y * dungeon::MAP_WIDTH + x]; }
dungeon::decoration dungeon::getDecoration(int x, int y) { return decorationMap[y * dungeon::MAP_WIDTH + x]; }

dungeon::dungeon() {
	for(int i = 0; i < MAP_WIDTH * MAP_HEIGHT; i++) {
		tile temp;
		map.push_back(temp);
		decoration tempDecoration;
		decorationMap.push_back(tempDecoration);
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
		for(int y = 0; y < MAP_HEIGHT; y++) {
			getTile(x, y).draw(window);
			getDecoration(x, y).draw(window);
		}
}

void dungeon::generateDungeon() {
	generateRooms();
	generateWalls();
	generateDecorations();
}

static const int MAX_ROOM_ATTEMPTS = 100;
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
			tileRoom(curRoom);
			decorateRoom(curRoom);

			rooms.push_back(curRoom);
			attempts = 0;
		} else
			attempts++;
	}
	for(int i = 0; i < rooms.size() - 1; i++)
		corridor(rooms[i], rooms[i + 1]);
}

//	Indices of filler floor tiles. Put here so that corridor method may use it.
static int fill[] = { 0, 61, 62, 63, 64 };

//	TODO: Make this take rooms as arguments.
//	Weird lower down wall glitch because we don't fill the corner of where the
//	corridors meet.
void dungeon::hCorridor(int x1, int x2, int y) {
	for(int x = std::min(x1, x2); x <= std::max(x1, x2); x++)
		for(int i = 0; i < CORRIDOR_SIZE; i++)
			map.at((y - CORRIDOR_SIZE/2 + i) * MAP_WIDTH + x) =
				dungeon::floor(x, y - CORRIDOR_SIZE/2 + i, fill[rand() % (sizeof(fill)/sizeof(int))]);
}
void dungeon::vCorridor(int y1, int y2, int x) {
	for(int y = std::min(y1, y2); y <= std::max(y1, y2); y++)
		for(int i = 0; i < CORRIDOR_SIZE; i++)
			map.at(y * MAP_WIDTH + x - CORRIDOR_SIZE/2 + i) =
				dungeon::floor(x - CORRIDOR_SIZE/2 + i, y, fill[rand() % (sizeof(fill)/sizeof(int))]);
}
void dungeon::corridor(room room1, room room2) {
	hCorridor(room1.center.x, room2.center.x, room2.center.y);
	vCorridor(room1.center.y, room2.center.y, room1.center.x);
}

//	Stores the indices of type of floor tiles we have.
static int topLeftCorner[] = { 1, 26, 60 };
static int topRightCorner[] = { 2, 27, 59 };
static int bottomLeftCorner[] = { 3, 28, 58 };
static int bottomRightCorner[] = { 4, 29, 57 };
static int topEdge[] = { 8, 9, 10 };
static int leftEdge[] = { 5, 6, 7 };
static int rightEdge[] = { 14, 15, 16 };
void dungeon::tileRoom(room area) {
	//	Decide whether to surround the room with stone tiles.
	bool surroundStone = rand() % 5 == 0;
	if(surroundStone) {
		for(int i = area.interior.left; i < area.interior.left + area.interior.width; i++) {
			if(i == area.interior.left || i == area.interior.left + area.interior.width - 1)
				for(int j = area.interior.top; j < area.interior.top + area.interior.height; j++)
					map.at(j * MAP_WIDTH + i) = dungeon::floor(i, j, 69);
			else
				map.at(area.interior.top * MAP_WIDTH + i) = dungeon::floor(i, area.interior.top, 69);
		}
		area.interior.left = area.interior.left + 1;
		area.interior.width = area.interior.width - 2;
		area.interior.top = area.interior.top + 1;
		area.interior.height = area.interior.height - 1;
	}

	//	Loops through each tile in room and chooses random index from the appriate array.
	for(int i = area.interior.left; i < area.interior.left + area.interior.width; i++)
		for(int j = area.interior.top; j < area.interior.top + area.interior.height; j++) {
			if(i == area.interior.left) {
				if(j == area.interior.top)
					map.at(j * MAP_WIDTH + i) = dungeon::floor(i, j, topLeftCorner[rand() % (sizeof(topLeftCorner)/sizeof(int))]);
				else
					map.at(j * MAP_WIDTH + i) = dungeon::floor(i, j, leftEdge[rand() % (sizeof(leftEdge)/sizeof(int))]);
			} else if(i == area.interior.left + area.interior.width - 1) {
				if(j == area.interior.top)
					map.at(j * MAP_WIDTH + i) = dungeon::floor(i, j, topRightCorner[rand() % (sizeof(topRightCorner)/sizeof(int))]);
				else
					map.at(j * MAP_WIDTH + i) = dungeon::floor(i, j, rightEdge[rand() % (sizeof(rightEdge)/sizeof(int))]);
			} else if(j == area.interior.top)
				map.at(j * MAP_WIDTH + i) = dungeon::floor(i, j, topEdge[rand() % (sizeof(topEdge)/sizeof(int))]);
			else
				map.at(j * MAP_WIDTH + i) = dungeon::floor(i, j, fill[rand() % (sizeof(fill)/sizeof(int))]);
		}
}


void dungeon::generateWalls() {
	/*
	*	Only want the four middle walls (hence the count % 4), starting at 1.
	*	Count serves to loop through which wall tile we use.
	*/
	int count = 1;
	for(int y = 0; y < MAP_HEIGHT - 1; y++)
		for(int x = 0; x < MAP_WIDTH; x++) {
			if(getTile(x, y).type == tile::EMPTY_T &&
				getTile(x, y + 1).type == tile::FLOOR_T) {
				map.at(y * MAP_WIDTH + x) = wall(x, y, count);
				count = 1 + count % 4;
			} else
				count = 1;
		}
}

void dungeon::decorateRoom(room area) {

}

void dungeon::generateDecorations() {
	for(int i = 0; i < map.size(); i++)
		if(map.at(i).type == tile::WALL_T && rand() % 20 == 0)
			decorationMap.at(i) = banner(i % MAP_WIDTH, i / MAP_WIDTH, rand() % banner::COUNT);
}
