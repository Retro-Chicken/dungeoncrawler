#include "tools.h"

namespace decorations {
	sf::IntRect rects[DECORATION_COUNT];
	int columns[DECORATION_COUNT];
	int counts[DECORATION_COUNT];
	std::string tags[DECORATION_COUNT];
	int layers[DECORATION_COUNT];
	float animTimes[ANIM_DECORATION_COUNT];

	void decorateRoom(tools::room area);

	void initialize() {
		rects[WALL] = sf::IntRect(0, 16, 16, 32);
		columns[WALL] = 7;
		counts[WALL] = 7;
		tags[WALL] = "wall";
		layers[WALL] = 0;

		rects[FLOOR] = sf::IntRect(0, 64, 16, 16);
		columns[FLOOR] = 30;
		counts[FLOOR] = 72;
		tags[FLOOR] = "floor";
		layers[FLOOR] = 0;

		rects[BANNER] = sf::IntRect(288, 128, 16, 32);
		columns[BANNER] = 6;
		counts[BANNER] = 6;
		tags[BANNER] = "banner";
		layers[BANNER] = 1;

		rects[DECORATION_COUNT - ANIM_DECORATION_COUNT + TORCH] = sf::IntRect(176, 254, 16, 32);
		columns[DECORATION_COUNT - ANIM_DECORATION_COUNT + TORCH] = 3;
		counts[DECORATION_COUNT - ANIM_DECORATION_COUNT + TORCH] = 3;
		tags[DECORATION_COUNT - ANIM_DECORATION_COUNT + TORCH] = "torch";
		layers[DECORATION_COUNT - ANIM_DECORATION_COUNT + TORCH] = 1;
		animTimes[TORCH] = 0.5;
	}

	drawable* instantiate(StaticDecoration type, int index) {
		return new staticdecoration(rects[type], columns[type], counts[type], index, tags[type], layers[type]);
	}
	drawable* instantiate(AnimatedDecoration type) {
		return new animateddecoration(rects[DECORATION_COUNT - ANIM_DECORATION_COUNT + type], columns[DECORATION_COUNT - ANIM_DECORATION_COUNT + type], counts[DECORATION_COUNT - ANIM_DECORATION_COUNT + type], animTimes[type], tags[DECORATION_COUNT - ANIM_DECORATION_COUNT + type], layers[DECORATION_COUNT - ANIM_DECORATION_COUNT + type]);
	}

	staticdecoration::staticdecoration(sf::IntRect spriteRect, int columns, int count, int index, std::string tag, int layer)
		: drawable(&params::tileTexture, sf::IntRect(spriteRect.left + spriteRect.width * (index % columns),
			spriteRect.top + spriteRect.height * (index/columns), spriteRect.width, spriteRect.height), layer) {
		this->tag = tag;
	}
	animateddecoration::animateddecoration(sf::IntRect spriteRect, int columns, int count, float animTime, std::string tag, int layer)
		: animation(&params::tileTexture, spriteRect, columns, count, animTime, layer) {
		this->tag = tag;
	}
};
