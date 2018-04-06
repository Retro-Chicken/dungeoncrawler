#include "player.h"

player::player(PlayerType pClass, Gender gender) {
	this->pClass = pClass;
	this->gender = gender;
}

player::~player() {

}

void player::update(float deltaTime) {
	//animations[animState].update(deltaTime);
}

void draw(sf::RenderWindow& window) {
	//animations[animState].draw(window);
}
