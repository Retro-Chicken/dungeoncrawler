#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#include "drawable.h"
#include "anchor.h"

class animation : public drawable {
public:
	animation(int x, int y, sf::Texture* texture, sf::IntRect startingFrame, int columns, int count, float animTime);
	animation(int x, int y, sf::Texture* texture, sf::IntRect startingFrame, int columns, int count, float animTime, int layer);
	animation(sf::Texture* texture, sf::IntRect startingFrame, int columns, int count, float animTime);
	animation(sf::Texture* texture, sf::IntRect startingFrame, int columns, int count, float animTime, int layer);
	animation(sf::Texture* texture, sf::IntRect startingFrame, int columns, int count, float animTime, anchor::ANCHOR anchorType);
	~animation();

	void update(float deltaTime) override;

private:
	sf::IntRect startingFrame;
	int columns = 0;
	int frame = 0;
	int count = 0;
	float totalTime;
	float frameTime;
};

#endif
