#include "dungeon.h"

tile& dungeon::getTile(int x, int y) { return map[y * params::MAP_WIDTH + x]; }
sf::Vector2i dungeon::getStart() {
	for(int x = 0; x < params::MAP_WIDTH; x++)
		for(int y = 0; y < params::MAP_HEIGHT; y++)
			if(getTile(x, y).walkable)
				return sf::Vector2i(x, y);
	return sf::Vector2i(0, 0);
}

dungeon::dungeon() {
	for(int i = 0; i < params::MAP_WIDTH * params::MAP_HEIGHT; i++)
		map.push_back(tile(i % params::MAP_WIDTH, i / params::MAP_WIDTH));
	params::tileTexture.loadFromFile("resources/tilesets/dungeon_tileset.png");
	generateDungeon();
}

dungeon::~dungeon() {
	for(int i = 0; i < map.size(); i++) map[i].clear();
}

void dungeon::update(float deltaTime) {
	for(int x = 0; x < params::MAP_WIDTH; x++)
		for(int y = 0; y < params::MAP_HEIGHT; y++)
			getTile(x, y).update(deltaTime);
}

void dungeon::draw(sf::RenderWindow& window) {
	for(int x = 0; x < params::MAP_WIDTH; x++)
		for(int y = 0; y < params::MAP_HEIGHT; y++)
			getTile(x, y).draw(window);
}

void dungeon::generateDungeon() {
	decorations::initialize();
	generateRooms();
	generateWalls();
	generateDecorations();
}

static const int MAX_ROOM_ATTEMPTS = 100;
void dungeon::generateRooms() {
	std::vector<tools::room> rooms;
	int roomCount = rand() % (params::MAX_ROOMS - params::MIN_ROOMS) + params::MIN_ROOMS;
	int attempts = 0;
	while(rooms.size() < roomCount && attempts < MAX_ROOM_ATTEMPTS) {
		int w = rand() % (params::MAX_ROOM_WIDTH - params::MIN_ROOM_WIDTH + 1) + params::MIN_ROOM_WIDTH;
		int h = rand() % (params::MAX_ROOM_HEIGHT - params::MIN_ROOM_HEIGHT) + params::MIN_ROOM_HEIGHT;
		int x = rand() % (params::MAP_WIDTH - w);
		int y = rand() % (params::MAP_HEIGHT - h - 1) + 1;
		tools::room curRoom(x, y, w, h);

		bool failed = false;
		for(int i = 0; i < rooms.size(); i++)
			if(rooms[i].intersects(curRoom)) {
				failed = true;
				break;
			}

		if(!failed) {
			tileRoom(curRoom);

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
	for(int x = std::min(x1, x2); x <= std::max(x1, x2); x++) {
		getTile(x, y).forceDrawable(decorations::instantiate(decorations::FLOOR, fill[rand() % (sizeof(fill)/sizeof(int))]));
		getTile(x, y).setWalkable(true);
	}
}
void dungeon::vCorridor(int y1, int y2, int x) {
	for(int y = std::min(y1, y2); y <= std::max(y1, y2); y++) {
		getTile(x, y).forceDrawable(decorations::instantiate(decorations::FLOOR, fill[rand() % (sizeof(fill)/sizeof(int))]));
		getTile(x, y).setWalkable(true);
	}
}
void dungeon::corridor(tools::room room1, tools::room room2) {
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
void dungeon::tileRoom(tools::room area) {
	//	Decide whether to surround the room with stone tiles.
	bool surroundStone = rand() % 5 == 0;
	if(surroundStone) {
		for(int i = area.interior.left; i < area.interior.left + area.interior.width; i++) {
			if(i == area.interior.left || i == area.interior.left + area.interior.width - 1)
				for(int j = area.interior.top; j < area.interior.top + area.interior.height; j++) {
					getTile(i, j).addDrawable(decorations::instantiate(decorations::FLOOR, 69));
					getTile(i, j).setWalkable(true);
				}
			else {
				getTile(i, area.interior.top).addDrawable(decorations::instantiate(decorations::FLOOR, 69));
				getTile(i, area.interior.top).setWalkable(true);
			}
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
				if(j == area.interior.top) {
					getTile(i, j).addDrawable(decorations::instantiate(decorations::FLOOR, topLeftCorner[rand() % (sizeof(topLeftCorner)/sizeof(int))]));
					getTile(i, j).setWalkable(true);
				} else {
					getTile(i, j).addDrawable(decorations::instantiate(decorations::FLOOR, leftEdge[rand() % (sizeof(leftEdge)/sizeof(int))]));
					getTile(i, j).setWalkable(true);
				}
			} else if(i == area.interior.left + area.interior.width - 1) {
				if(j == area.interior.top) {
					getTile(i, j).addDrawable(decorations::instantiate(decorations::FLOOR, topRightCorner[rand() % (sizeof(topRightCorner)/sizeof(int))]));
					getTile(i, j).setWalkable(true);
				} else {
					getTile(i, j).addDrawable(decorations::instantiate(decorations::FLOOR, rightEdge[rand() % (sizeof(rightEdge)/sizeof(int))]));
					getTile(i, j).setWalkable(true);
				}
			} else if(j == area.interior.top) {
				getTile(i, j).addDrawable(decorations::instantiate(decorations::FLOOR, topEdge[rand() % (sizeof(topEdge)/sizeof(int))]));
				getTile(i, j).setWalkable(true);
			} else {
				getTile(i, j).addDrawable(decorations::instantiate(decorations::FLOOR, fill[rand() % (sizeof(fill)/sizeof(int))]));
				getTile(i, j).setWalkable(true);
			}
		}
}


void dungeon::generateWalls() {
	/*
	*	Only want the four middle walls (hence the count % 4), starting at 1.
	*	Count serves to loop through which wall tile we use.
	*/
	int count = 1;
	for(int y = 0; y < params::MAP_HEIGHT - 1; y++)
		for(int x = 0; x < params::MAP_WIDTH; x++) {
			if(getTile(x, y).isEmpty() && !getTile(x, y + 1).isEmpty()) {
				getTile(x, y).addDrawable(decorations::instantiate(decorations::WALL, count));
				count = 1 + count % 4;
			} else
				count = 1;
		}
}

void dungeon::generateDecorations() {
	for(int x = 0; x < params::MAP_WIDTH; x++)
		for(int y = 0; y < params::MAP_HEIGHT; y++) {
			if(getTile(x, y).getTag() == "wall" && rand() % 20 == 0)
				getTile(x, y).addDrawable(decorations::instantiate(decorations::BANNER, rand() % decorations::counts[decorations::BANNER]));
			if(getTile(x, y).getTag() == "wall" && rand() % 20 == 0)
				getTile(x, y).addDrawable(decorations::instantiate(decorations::TORCH));
		}
}
