#ifndef TOOLS_H
#define TOOLS_H

#include <SFML/Graphics.hpp>
#include "dungeonparams.h"
#include "../rendertools/drawable.h"
#include "../rendertools/animation.h"

namespace decorations {
	const int DECORATION_COUNT = 6;

	enum DecorationType { WALL, FLOOR, BANNER, TORCH };

	extern void initialize();

	extern drawable* instantiate(DecorationType type);
	extern drawable* instantiate(DecorationType type, int index);

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
};

namespace tools {

};

#endif
