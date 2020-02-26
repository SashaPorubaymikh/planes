#include "main.hpp"

extern sf::Texture PEOPLE[4];
extern int SCREEN_SIZE[2];
extern float SCREEN_DIFF;

People::People(int x, int y) {
	short int type = rand()%4;
	rotateRight = true;
	goRight = rand()%2;

	sprite.setTexture(PEOPLE[type]);
	sf::Rect<float> tempRect = sprite.getGlobalBounds();
	sprite.setOrigin(tempRect.left + tempRect.width / 2, tempRect.top + tempRect.height / 2);
	sprite.setScale(4 * SCREEN_DIFF, 4 * SCREEN_DIFF);
	sprite.setRotation(-30 + rand()%60);
	sprite.setPosition(x, y);
}

bool People::draw(sf::RenderWindow &window) {
	if (rotateRight) sprite.rotate(4);
	else sprite.rotate(-4);

	if (std::abs(30 - sprite.getRotation()) < 5) {
		rotateRight = false;
		sprite.scale(-1, 1);
	}
	else if (std::abs(330 - sprite.getRotation()) < 5) {
		rotateRight = true;
		sprite.scale(-1, 1);
	}

	sf::Rect<float> posRect = sprite.getGlobalBounds();
	if (posRect.left + posRect.width <= 0 or posRect.left > SCREEN_SIZE[0] + 10) return false;
	if (goRight) sprite.move(SCREEN_DIFF, 0);
	else sprite.move(-SCREEN_DIFF, 0);


	window.draw(sprite);
	return true;
}
