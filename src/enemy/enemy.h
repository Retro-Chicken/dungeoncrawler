#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include "../config.h"
#include "../util.h"
#include "../ai/path.h"
#include "../rendertools/animation.h"
#include "../rendertools/anchor.h"
#include <math.h>

class enemy {
public:
	enum EnemyType { CLERIC = 0, WARRIOR = 1, RANGER = 2, WIZARD = 3, ROGUE = 4 };
	enum AnimationStates { IDLE = 0, GESTURE = 1, WALK = 2, ATTACK = 3, DEATH = 4 };

	enemy(EnemyType eClass);
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

private:
	static sf::Texture charTexture[5];

	static int ANIM_COUNT;
	static int ANIM_FRAMES;
	static float ANIM_SPEED;

	//	Pixels per second
	static float speed;

	sf::Vector2f position;
	AnimationStates animState = IDLE;
	bool walkingBackwards = false;
	EnemyType eClass = CLERIC;

	path currentPath;

	std::vector<animation> animations;
};

#endif
