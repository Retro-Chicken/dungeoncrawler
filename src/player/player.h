#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "../config.h"
#include "../util.h"
#include "../ai/path.h"
#include "../rendertools/animation.h"
#include "../rendertools/anchor.h"
#include <math.h>

class player {
public:
	enum PlayerType { CLERIC = 0, WARRIOR = 1, RANGER = 2, WIZARD = 3, ROGUE = 4 };
	enum Gender { MALE, FEMALE };
	enum AnimationStates { IDLE = 0, GESTURE = 1, WALK = 2, ATTACK = 3, DEATH = 4 };

	player(PlayerType pClass, Gender gender);
	~player();

	void update(float deltaTime);
	void draw(sf::RenderWindow& window);

	sf::Vector2f getPosition() { return position; }
	void setPosition(sf::Vector2f position);
	void setPosition(sf::Vector2i position);

	void setPath(path newPath);

	void setAnimState(AnimationStates animState) { this->animState = animState; }

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
	PlayerType pClass = CLERIC;
	Gender gender = MALE;

	path currentPath;

	std::vector<animation> animations;
};

#endif
