#include "tools.h"

namespace decorations {
	void decorateRoom(const tools::room& area, std::vector<tile>& map) {
		int prob = rand() % 100;
		if(prob <= 50) {
			//	Floor decorations nothing else.
			for(int i = 0; i < 3; i++) {
				int x = area.interior.left + rand() % area.interior.width;
				int y = area.interior.top + rand() % area.interior.height;
				map[y * params::MAP_WIDTH + x].addDrawable(instantiate(FLOOR_DECOR, rand()));
			}
		} else if(prob <= 80) {
			//	Table layout.
			std::cout << "Making chair" << std::endl;
			int x = area.interior.left + 2 + rand() % (area.interior.width - 2);
			int y = area.interior.top + 2 + rand() % (area.interior.height - 2);
			map[y * params::MAP_WIDTH + x].addDrawable(instantiate(TABLE, 0));
			map[y * params::MAP_WIDTH + x].addDrawable(instantiate(CHAIR, 2));
			for(int i = x; i < x + rects[TABLE].width/16; i++)
				for(int j = y; j < y + rects[TABLE].height/16; j++)
					map[(j - 1) * params::MAP_WIDTH + i].walkable = false;
		} else if(prob <= 100) {
			//	Altar layout.
			std::cout << "Making altar" << std::endl;
			for(int x = area.center.x - 1; x <= area.center.x + 1; x++)
				for(int y = area.center.y - 1; x <= area.center.y + 1; y++)
					map[y * params::MAP_WIDTH + x].forceDrawable(instantiate(FLOOR, 69));
			map[area.center.y * params::MAP_WIDTH + area.center.x].addDrawable(instantiate(ALTAR, rand()));
			map[area.center.y * params::MAP_WIDTH + area.center.x].walkable = false;
		}
	}

	sf::IntRect rects[DECORATION_COUNT];
	int columns[DECORATION_COUNT];
	int counts[DECORATION_COUNT];
	std::string tags[DECORATION_COUNT];
	int layers[DECORATION_COUNT];
	float animTimes[ANIM_DECORATION_COUNT];

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

		rects[ALTAR] = sf::IntRect(304, 256, 16, 32);
		columns[ALTAR] = 4;
		counts[ALTAR] = 4;
		tags[ALTAR] = "altar";
		layers[ALTAR] = 1;

		rects[FLOOR_DECOR] = sf::IntRect(96, 192, 16, 16);
		columns[FLOOR_DECOR] = 3;
		counts[FLOOR_DECOR] = 3;
		tags[FLOOR_DECOR] = "floor decor";
		layers[FLOOR_DECOR] = 1;

		rects[CRATE] = sf::IntRect(0, 256, 16, 16);
		columns[CRATE] = 2;
		counts[CRATE] = 2;
		tags[CRATE] = "crate";
		layers[CRATE] = 1;

		rects[BARREL] = sf::IntRect(64, 256, 16, 16);
		columns[BARREL] = 2;
		counts[BARREL] = 2;
		tags[BARREL] = "barrel";
		layers[BARREL] = 1;

		rects[CHAIR] = sf::IntRect(208, 194, 16, 32);
		columns[CHAIR] = 4;
		counts[CHAIR] = 4;
		tags[CHAIR] = "chair";
		layers[CHAIR] = 2;

		rects[TABLE] = sf::IntRect(288, 195, 32, 32);
		columns[TABLE] = 1;
		counts[TABLE] = 1;
		tags[TABLE] = "table";
		layers[TABLE] = 1;

		rects[DECORATION_COUNT - ANIM_DECORATION_COUNT + TORCH] = sf::IntRect(176, 254, 16, 32);
		columns[DECORATION_COUNT - ANIM_DECORATION_COUNT + TORCH] = 3;
		counts[DECORATION_COUNT - ANIM_DECORATION_COUNT + TORCH] = 3;
		tags[DECORATION_COUNT - ANIM_DECORATION_COUNT + TORCH] = "torch";
		layers[DECORATION_COUNT - ANIM_DECORATION_COUNT + TORCH] = 1;
		animTimes[TORCH] = 0.5;
	}

	drawable* instantiate(StaticDecoration type, int index) {
		if(index >= counts[type])
			index %= counts[type];
		return new staticdecoration(rects[type], columns[type], counts[type], index, tags[type], layers[type]);
	}
	drawable* instantiate(StaticDecoration type, int index, anchor::ANCHOR anch) {
		drawable* result = instantiate(type, index);
		result->setAnchor(anch);
		return result;
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
