#ifndef DUNGEON_PARAMS
#define DUNGEON_PARAMS

#include <SFML/Graphics.hpp>

namespace params {
	//	Dungeon settings.
	static const int MAP_HEIGHT = 50, MAP_WIDTH = 75;

	extern const int MAX_ROOMS;
	extern const int MIN_ROOMS;
	extern const int MIN_ROOM_WIDTH, MAX_ROOM_WIDTH;
	extern const int MIN_ROOM_HEIGHT, MAX_ROOM_HEIGHT;
	extern const int ROOM_BUFFER;
	extern const int CORRIDOR_SIZE;

	//	Texture settings.
	extern sf::Texture tileTexture;
};

#endif
