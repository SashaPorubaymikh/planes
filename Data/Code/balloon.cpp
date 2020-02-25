#include "main.hpp"

extern sf::Texture BALLOONS[3];
extern float SCREEN_DIFF;
extern int SCREEN_SIZE[2];

Balloon::Balloon() {
	reset();
	sprite.setScale(4, 4);
}

void Balloon::reset() {
	sprite.setTexture(BALLOONS[rand()%3]);
	speed = (float)((float)1 + (float)(rand()%2)) / 10;
	goRight = rand()%2;
	sf::Rect<float> balloonRect = sprite.getGlobalBounds();
	goRight ? sprite.setPosition(-55000 + rand()%(50000 - (int)balloonRect.width), 50 + rand()%200) : sprite.setPosition(SCREEN_SIZE[0] + 55000 - rand()%50000, 50 + rand()%150);
}

void Balloon::draw(sf::RenderWindow *window) {
	goRight ? sprite.move(speed * SCREEN_DIFF, 0) : sprite.move(-speed * SCREEN_DIFF, 0);
	sf::Rect<float> balloonRect = sprite.getGlobalBounds();
	if ((goRight and balloonRect.left > SCREEN_SIZE[0]) or (!goRight and balloonRect.left + balloonRect.width < 0)) reset();
	balloonRect = sprite.getGlobalBounds();
	if (balloonRect.left + balloonRect.width >= 0 and balloonRect.left <= SCREEN_SIZE[0]) window->draw(sprite);
}