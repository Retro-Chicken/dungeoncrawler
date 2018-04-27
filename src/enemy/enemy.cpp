#include "enemy.h"

float enemy::speed = 40;
sf::Texture enemy::charTexture[5];
int enemy::ANIM_COUNT = 5;
int enemy::ANIM_FRAMES = 10;
float enemy::ANIM_SPEED = 0.1;

enemy::enemy(EnemyType eClass, EnemyVariant variant, player* target) {
	this->eClass = eClass;
	this->target = target;

	charTexture[SKELETON].loadFromFile("resources/tilesets/skeleton.png");
	charTexture[GOBLIN].loadFromFile("resources/tilesets/goblin.png");
	charTexture[ORC].loadFromFile("resources/tilesets/orc.png");
	for(int i = 0; i < ANIM_COUNT; i++)
		animations.push_back(animation(&charTexture[eClass], sf::IntRect(0, 32*i + 32*ANIM_COUNT*(eClass != SKELETON ? variant : 0), 32, 32), ANIM_FRAMES, ANIM_FRAMES, ANIM_SPEED*ANIM_FRAMES, anchor::ANCHOR_PLAYER));
}

enemy::~enemy() {

}

void enemy::setPosition(sf::Vector2f position) {
	this->position = position;
}
void enemy::setPosition(sf::Vector2i position) {
	this->position.x = position.x;
	this->position.y = position.y;
}

void enemy::setPath(path newPath) {
	if(!currentPath.isEmpty() && tilesMoved <= 1) return;
	if(newPath.points.size() <= 3) { currentPath = path(); return; }
	currentPath = newPath;
	walkingBackwards = newPath.points[newPath.points.size()].x * config::TILE_SIZE < (int)position.x;
	tilesMoved = 0;
}

void enemy::update(float deltaTime) {
	animState = IDLE;
	if(!currentPath.isEmpty()) {
		animState = WALK;
		int sx = util::sgn(currentPath.top().x * config::TILE_SIZE - position.x);
		int sy = util::sgn(currentPath.top().y * config::TILE_SIZE - position.y);
		walkingBackwards = sx < 0 || (sx == 0 && walkingBackwards);
		position.x += sx*speed*deltaTime;
		position.y += sy*speed*deltaTime;
		if(fabs(position.x - currentPath.top().x * config::TILE_SIZE) < 1)
			position.x = currentPath.top().x * config::TILE_SIZE;
		if(fabs(position.y - currentPath.top().y * config::TILE_SIZE) < 1)
			position.y = currentPath.top().y * config::TILE_SIZE;
		if(sf::Vector2i((int)position.x, (int)position.y) == currentPath.top() * (int)config::TILE_SIZE) {
			currentPath.pop();
			tilesMoved++;
		}
	}
	animations[animState].update(deltaTime);
	animations[animState].setPosition((int)position.x, (int)position.y);
}

void enemy::draw(sf::RenderWindow& window) {
	animations[animState].draw(window, walkingBackwards);
}
