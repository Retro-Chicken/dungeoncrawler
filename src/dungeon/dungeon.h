#ifndef DUNGEON_H
#define DUNGEON_H

#include <SFML/Graphics.hpp>
#include <set>
#include "../config.h"
#include "../rendertools/drawable.h"
#include "../rendertools/animation.h"

class dungeon {
public:
	dungeon();
	~dungeon();

	void update(float deltaTime);
	void draw(sf::RenderWindow& window);

	static const int MAP_HEIGHT = 50, MAP_WIDTH = 75;

private:
	//	Dungeon settings.
	static const int MAX_ROOMS = 4;
	static const int MIN_ROOMS = 2;
	static const int MIN_ROOM_WIDTH = 10, MAX_ROOM_WIDTH = 20;
	static const int MIN_ROOM_HEIGHT = 7, MAX_ROOM_HEIGHT = 20;
	static const int ROOM_BUFFER = 2;
	static const int CORRIDOR_SIZE = 1;

	//	Texture settings.
	static sf::Texture tileTexture;

	//	Method to randomly generate dungeon.
	void generateDungeon();

	//	Methods used to generate different layers of the dungeon.
	void generateRooms();
	void generateWalls();
	void generateDecorations();
	//	Methods to connect two rooms of the dungeon.
	void hCorridor(int x1, int x2, int y);
	void vCorridor(int y1, int y2, int x);

	struct room {
		sf::IntRect interior;
		sf::Vector2i center;

		room(int x, int y, int w, int h) : interior(x, y, w, h) {
			center.x = interior.left + interior.width/2;
			center.y = interior.top + interior.height/2;
		}
		sf::IntRect bufferBounds() {
			return sf::IntRect(interior.left - ROOM_BUFFER, interior.top - ROOM_BUFFER,
				interior.width + 2*ROOM_BUFFER, interior.height + 2*ROOM_BUFFER);
		}

		bool intersects(room room2) {
			return bufferBounds().intersects(room2.bufferBounds());
		}
	};

	struct drawablecompare
	{
		bool operator()(const drawable* lhs, const drawable* rhs) const  { return *lhs < *rhs; }
	};

	struct tile {
		bool isEmpty() { return graphics.size() == 0; }
		bool walkable = false;
		void setWalkable(bool walkable) { this->walkable = walkable; }
		int x = 0;
		int y = 0;
		std::set<drawable*, drawablecompare> graphics;
		tile(int x, int y) {
			this->x = x;
			this->y = y;
		}
		void clear() {
			for(drawable* graphic : graphics) delete graphic;
		}

		void addDrawable(drawable* item) {
			item->setPosition(x, y);
			graphics.insert(item);
		}

		void forceDrawable(drawable* item) {
			if(graphics.find(item) != graphics.end())
				graphics.erase(item);
			addDrawable(item);
		}

		void draw(sf::RenderWindow& window) const {
			for(drawable* graphic : graphics)
				graphic->draw(window);
		}

		void update(float deltaTime) {
			for(drawable* graphic : graphics)
				graphic->update(deltaTime);
		}

		std::string getTag() { return graphics.size() > 0 ? (*graphics.begin())->tag : ""; }
	};

	class wall : public drawable {
	public:
		static const sf::IntRect WALL;
		static const int COLUMNS = 7, COUNT = 7;
		wall(int index) : drawable(&tileTexture, sf::IntRect(WALL.left + WALL.width * (index % COLUMNS),
			WALL.top + WALL.height * (index/COLUMNS), WALL.width, WALL.height), 0) {
			tag = "wall";
		}
	};
	class floor : public drawable {
	public:
		static const sf::IntRect FLOOR;
		static const int COLUMNS = 30, COUNT = 72;
		floor(int index) : drawable(&tileTexture, sf::IntRect(FLOOR.left + FLOOR.width * (index % COLUMNS),
			FLOOR.top + FLOOR.height * (index/COLUMNS), FLOOR.width, FLOOR.height), 0) {
			tag = "floor";
		}
	};
	class banner : public drawable {
	public:
		static const sf::IntRect BANNER;
		static const int COLUMNS = 6, COUNT = 6;
		banner(int index) : drawable(&tileTexture, sf::IntRect(BANNER.left + BANNER.width * (index % COLUMNS),
			BANNER.top + BANNER.height * (index/COLUMNS), BANNER.width, BANNER.height), 1) {
			tag = "banner";
		}
	};
	class torch : public animation {
	public:
		static const sf::IntRect TORCH;
		static const int COLUMNS = 3, COUNT = 3;
		torch() : animation(&tileTexture, TORCH, COLUMNS, COUNT, 0.5, 1) {
			tag = "torch";
		}
	};

	void corridor(room room1, room room2);
	void tileRoom(room area);
	void decorateRoom(room area);

	//	TODO: Figure out why I can only use a vector and not an array.
	std::vector<tile> map;
	tile& getTile(int x, int y);
};

#endif
