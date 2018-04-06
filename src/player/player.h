#ifndef PLAYER_H
#define PLAYER_H

#include "../config.h"
#include <SFML/Graphics.hpp>
#include "../rendertools/animation.h"

class player {
public:
	enum PlayerType { CLERIC, WARRIOR, RANGER, WIZARD, ROGUE };
	enum Gender { MALE, FEMALE };
	enum AnimationStates { IDLE = 0, GESTURE = 1, WALK = 2, ATTACK = 3, DEATH = 4 };

	player(PlayerType pClass, Gender gender);
	~player();

	void update(float deltaTime);
	void draw(sf::RenderWindow& window);

	sf::Vector2i getPosition() { return position; }
	void setPosition(sf::Vector2i position) { this->position = position; }

	void setAnimState(AnimationStates animState) { this->animState = animState; }

private:
	sf::Vector2i position;
	AnimationStates animState = IDLE;
	PlayerType pClass = CLERIC;
	Gender gender = MALE;
	//animation animations[5];
};

#endif
