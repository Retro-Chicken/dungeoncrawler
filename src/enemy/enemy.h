#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include "../config.h"
#include "../util.h"
#include "../ai/path.h"
#include "../rendertools/animation.h"
#include "../rendertools/anchor.h"
#include "../player/player.h"
#include "../ai/astar.h"
#include <math.h>

class enemy {
public:
	enum EnemyType { SKELETON = 0, ORC = 1, GOBLIN = 2 };
	enum EnemyVariant { ONE = 0, TWO = 1 };
	enum AnimationStates { IDLE = 0, GESTURE = 1, WALK = 2, ATTACK = 3, DEATH = 4 };

	enemy(EnemyType eClass, EnemyVariant variant, player* target);
	~enemy();
	void update(float deltaTime);
	void draw(sf::RenderWindow& window);

	sf::Vector2f getPosition() { return position; }
	void setPosition(sf::Vector2f position);
	void setPosition(sf::Vector2i position);

	void setPath(path newPath);

	void setAnimState(AnimationStates animState) { this->animState = animState; }

	path getPath() { return currentPath; }
	bool pathEmpty() { return currentPath.isEmpty(); }

	player* getTarget() { return target; }

private:
	static sf::Texture charTexture[5];

	player* target;

	static int ANIM_COUNT;
	static int ANIM_FRAMES;
	static float ANIM_SPEED;

	//	Pixels per second
	static float speed;

	int tilesMoved = 0;

	sf::Vector2f position;
	AnimationStates animState = IDLE;
	bool walkingBackwards = false;
	EnemyType eClass = SKELETON;

	path currentPath;

	std::vector<animation> animations;
};

#endif
