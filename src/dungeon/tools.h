#ifndef TOOLS_H
#define TOOLS_H

#include <SFML/Graphics.hpp>
#include "dungeonparams.h"
#include "../rendertools/drawable.h"
#include "../rendertools/animation.h"

namespace decorations {
	class wall : public drawable {
	public:
		static const sf::IntRect WALL;
		static const int COLUMNS = 7, COUNT = 7;
		wall(int index);
	};
	class floor : public drawable {
	public:
		static const sf::IntRect FLOOR;
		static const int COLUMNS = 30, COUNT = 72;
		floor(int index);
	};
	class banner : public drawable {
	public:
		static const sf::IntRect BANNER;
		static const int COLUMNS = 6, COUNT = 6;
		banner(int index);
	};
	class torch : public animation {
	public:
		static const sf::IntRect TORCH;
		static const int COLUMNS = 3, COUNT = 3;
		torch();
	};
};

namespace tools {

};

#endif
