#include "player.h"

float player::speed = 8;
sf::Texture player::charTexture;

player::player(PlayerType pClass, Gender gender) {
	this->pClass = pClass;
	this->gender = gender;

	charTexture.loadFromFile("resources/tilesets/dungeon_tileset.png");
	animations.push_back(animation(&charTexture, sf::IntRect(193, 368, 16, 32), 1, 1, 10));
}

player::~player() {

}

void player::setPosition(sf::Vector2f position) {
	this->position = position;
}
void player::setPosition(sf::Vector2i position) {
	this->position.x = position.x;
	this->position.y = position.y;
}

void player::update(float deltaTime) {
	if(!currentPath.isEmpty()) {
		int sx = util::sgn(currentPath.top().x - position.x);
		int sy = util::sgn(currentPath.top().y - position.y);
		position.x += sx*speed*deltaTime;
		position.y += sy*speed*deltaTime;
		if(sx*position.x > sx*currentPath.top().x)
			position.x = currentPath.top().x;
		if(sy*position.y > sy*currentPath.top().y)
			position.y = currentPath.top().y;
		if(sf::Vector2i((int)position.x, (int)position.y) == currentPath.top())
			currentPath.pop();
	}
	animations[animState].update(deltaTime);
}

void player::draw(sf::RenderWindow& window) {
	animations[animState].setPosition((int)position.x, (int)position.y);
	animations[animState].draw(window);
}
