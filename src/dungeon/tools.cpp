#include "tools.h"

namespace decorations {
	sf::IntRect rects[DECORATION_COUNT];
	int columns[DECORATION_COUNT];
	int counts[DECORATION_COUNT];
	std::string tags[DECORATION_COUNT];
	int layers[DECORATION_COUNT];

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

		rects[TORCH] = sf::IntRect(176, 254, 16, 32);
		columns[TORCH] = 3;
		counts[TORCH] = 3;
		tags[TORCH] = "torch";
		layers[TORCH] = 1;
	}

	drawable* instantiate(DecorationType type, int index) {
		if(type == TORCH)
			return new animateddecoration(rects[type], columns[type], counts[type], 0.5f, tags[type], layers[type]);
		return new staticdecoration(rects[type], columns[type], counts[type], index, tags[type], layers[type]);
	}
	drawable* instantiate(DecorationType type) {
		return instantiate(type, 0);
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
