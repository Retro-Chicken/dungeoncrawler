#ifndef ANCHOR_H
#define ANCHOR_H

#include <SFML/Graphics.hpp>
#include "../config.h"

class anchor {
public:
	enum ANCHOR { ANCHOR_TOP_LEFT, ANCHOR_TOP_RIGHT,
		ANCHOR_BOTTOM_LEFT, ANCHOR_BOTTOM_RIGHT, ANCHOR_CENTER,
	 	ANCHOR_PLAYER };

	static void anchorSprite(sf::Sprite& sprite, ANCHOR type) {
		switch(type) {
			case ANCHOR_TOP_LEFT:
				break;
			case ANCHOR_BOTTOM_LEFT:
				sprite.setPosition(sprite.getPosition().x,
					sprite.getPosition().y - sprite.getTextureRect().height);
				break;
			case ANCHOR_TOP_RIGHT:
				sprite.setPosition(sprite.getPosition().x - sprite.getTextureRect().width,
					sprite.getPosition().y);
				break;
			case ANCHOR_BOTTOM_RIGHT:
				sprite.setPosition(sprite.getPosition().x - sprite.getTextureRect().width,
					sprite.getPosition().y - sprite.getTextureRect().height);
				break;
			case ANCHOR_CENTER:
				sprite.setPosition(sprite.getPosition().x - sprite.getTextureRect().width/2,
					sprite.getPosition().y - sprite.getTextureRect().height/2);
				break;
			case ANCHOR_PLAYER:
				sprite.setPosition(sprite.getPosition().x - 8, sprite.getPosition().y - 24);
				break;
		}
	}
};

#endif
