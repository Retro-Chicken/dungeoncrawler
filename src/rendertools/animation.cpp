#include "animation.h"
#include <iostream>

animation::animation(sf::Texture* texture, sf::IntRect startingFrame, int columns, int count, float animTime, int layer)
	: animation(0, 0, texture, startingFrame, columns, count, animTime, layer) {}

animation::animation(sf::Texture* texture, sf::IntRect startingFrame, int columns, int count, float animTime)
	: animation(0, 0, texture, startingFrame, columns, count, animTime, 0) {}

animation::animation(int x, int y, sf::Texture* texture, sf::IntRect startingFrame, int columns, int count, float animTime)
	: animation(x, y, texture, startingFrame, columns, count, animTime, 0) {}

animation::animation(int x, int y, sf::Texture* texture, sf::IntRect startingFrame, int columns, int count, float animTime, int layer)
	: drawable(x, y, texture, startingFrame, layer) {
	this->columns = columns;
	this->count = count;
	this->startingFrame = startingFrame;
	frameTime = animTime / count;
}

animation::~animation() {}

void animation::update(float deltaTime) {
	totalTime += deltaTime;
	std::cout << totalTime << " " << frameTime << std::endl; 
	while(totalTime >= frameTime) {
		std::cout << "SWITCHED BOI" << std::endl;
		totalTime -= frameTime;
		frame++;
		frame %= count;
		sprite.setTextureRect(sf::IntRect(startingFrame.left + startingFrame.width * (frame % columns),
			startingFrame.top + startingFrame.height * (frame / columns), startingFrame.width, startingFrame.height));
	}
}
