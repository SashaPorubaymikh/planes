#include "main.hpp"

extern sf::Texture CLOUDS[3];
extern int SCREEN_SIZE[2];
extern float SCREEN_DIFF;

Cloud::Cloud() {
	sprite.setTexture(CLOUDS[rand()%3]);
	sprite.setScale(4 * SCREEN_DIFF, 4 * SCREEN_DIFF);
	reset();
}

void Cloud::reset() {
	speed = float(2 + rand()%5) / 10 * SCREEN_DIFF;
	sprite.setPosition(SCREEN_SIZE[0] + rand()%1000, 50 + rand()%200);
	sprite.setColor(sf::Color(255, 255, 255, 100 + rand()%156));
}

void Cloud::draw(sf::RenderWindow &window) {
	sprite.move(-speed, 0);
	sf::Rect<float> cloudRect = sprite.getGlobalBounds();
	if (cloudRect.left + cloudRect.width < -10) reset();
	if (cloudRect.left + cloudRect.width > 0 and cloudRect.left < SCREEN_SIZE[0]) window.draw(sprite);
}