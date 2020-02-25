#include "main.hpp"

extern sf::Texture EXPLOSIONS[8];
extern float SCREEN_DIFF;

Explosion::Explosion (sf::Rect<float> posRect) {
	explosionSprite.setTexture(EXPLOSIONS[5]);
	explosionSprite.setTexture(EXPLOSIONS[0]);
	explosionSprite.setScale(4 * SCREEN_DIFF, 4 * SCREEN_DIFF);
	explosionSprite.setPosition(posRect.left, posRect.top);
	timer = 0;
}

bool Explosion::draw(sf::RenderWindow *window) {
	timer++;
	if (timer % 8 == 0 and timer < 64) {
		explosionSprite.setTexture(EXPLOSIONS[timer / 8]);
	}
	if (timer == 64) return false;
	window->draw(explosionSprite);
	return true;
}