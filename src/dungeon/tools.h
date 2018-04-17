#ifndef TOOLS_H
#define TOOLS_H

#include <SFML/Graphics.hpp>
#include "dungeonparams.h"
#include "../rendertools/drawable.h"
#include "../rendertools/animation.h"
#include "tile.h"
#include "../rendertools/anchor.h"

#include <iostream>

namespace tools {
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
};

namespace decorations {
	const int DECORATION_COUNT = 10;
	const int ANIM_DECORATION_COUNT = 1;

	enum StaticDecoration { WALL, FLOOR, BANNER, ALTAR, FLOOR_DECOR, CRATE, BARREL, CHAIR, TABLE };
	enum AnimatedDecoration { TORCH };

	extern void decorateRoom(const tools::room& area, std::vector<tile>& map);

	extern void initialize();

	extern drawable* instantiate(AnimatedDecoration type);
	extern drawable* instantiate(StaticDecoration type, int index);
	extern drawable* instantiate(StaticDecoration type, int index, anchor::ANCHOR anch);

	class staticdecoration : public drawable {
	public:
		staticdecoration(sf::IntRect spriteRect, int columns, int count, int index, std::string tag, int layer);
	};
	class animateddecoration : public animation {
	public:
		animateddecoration(sf::IntRect spriteRect, int columns, int count, float animTime, std::string tag, int layer);
	};

	extern sf::IntRect rects[DECORATION_COUNT];
	extern int columns[DECORATION_COUNT];
	extern int counts[DECORATION_COUNT];
	extern std::string tags[DECORATION_COUNT];
	extern int layers[DECORATION_COUNT];
	extern float animTimes[ANIM_DECORATION_COUNT];
};

#endif
