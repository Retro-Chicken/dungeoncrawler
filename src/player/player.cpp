#include "player.h"

float player::speed = 64;
sf::Texture player::charTexture[5];
int player::ANIM_COUNT = 5;
int player::ANIM_FRAMES = 10;
float player::ANIM_SPEED = 0.1;

player::player(PlayerType pClass, Gender gender) {
	this->pClass = pClass;
	this->gender = gender;

	charTexture[CLERIC].loadFromFile("resources/tilesets/cleric.png");
	charTexture[WARRIOR].loadFromFile("resources/tilesets/warrior.png");
	charTexture[RANGER].loadFromFile("resources/tilesets/ranger.png");
	charTexture[WIZARD].loadFromFile("resources/tilesets/wizard.png");
	charTexture[ROGUE].loadFromFile("resources/tilesets/rogue.png");
	for(int i = 0; i < ANIM_COUNT; i++)
		animations.push_back(animation(&charTexture[pClass], sf::IntRect(0, 32*i, 32, 32), ANIM_FRAMES, ANIM_FRAMES, ANIM_SPEED*ANIM_FRAMES, anchor::ANCHOR_PLAYER));
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
	animState = IDLE;
	if(!currentPath.isEmpty()) {
		animState = WALK;
		int sx = util::sgn(currentPath.top().x * config::TILE_SIZE - position.x);
		int sy = util::sgn(currentPath.top().y * config::TILE_SIZE - position.y);
		walkingBackwards = sx < 0 || (sx == 0 && walkingBackwards);
		position.x += sx*speed*deltaTime;
		position.y += sy*speed*deltaTime;
		if(sx*position.x > sx*(currentPath.top().x * config::TILE_SIZE))
			position.x = currentPath.top().x * config::TILE_SIZE;
		if(sy*position.y > sy*(currentPath.top().y * config::TILE_SIZE))
			position.y = currentPath.top().y * config::TILE_SIZE;
		if(sf::Vector2i((int)position.x, (int)position.y) == currentPath.top() * (int)config::TILE_SIZE)
			currentPath.pop();
	}
	animations[animState].update(deltaTime);
	animations[animState].setPosition((int)position.x, (int)position.y);
}

void player::draw(sf::RenderWindow& window) {
	animations[animState].draw(window, animState == WALK ? walkingBackwards : false);
}
