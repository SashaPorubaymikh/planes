#include "main.hpp"

extern sf::Texture PARATROOPERS[4][2];
extern int SCREEN_SIZE[2];
extern float SCREEN_DIFF;

Paratrooper::Paratrooper (int x, int y, int colorNum) {
	type = colorNum;
	sprite.setTexture(PARATROOPERS[colorNum][0]);
	sf::Rect<float> tempRect = sprite.getGlobalBounds();
	sprite.setOrigin(tempRect.left + tempRect.width / 2, (tempRect.top + tempRect.height / 3) * 2);
	sprite.setScale(4 * SCREEN_DIFF, 4 * SCREEN_DIFF);
	sprite.setPosition(x + 30 * SCREEN_DIFF, y + 10 * SCREEN_DIFF);

	isLanded = isDowned = false;
	rotateRight = true;
	downedAnimCount = 0;
}

bool Paratrooper::draw(sf::RenderWindow &window) {
	if (!isLanded and !isDowned) {
		sprite.move(0, SCREEN_DIFF);
		sf::Rect<float> spriteRect = sprite.getGlobalBounds();
		if (spriteRect.top + spriteRect.height >= SCREEN_SIZE[1] - 10 * SCREEN_DIFF) land();
	}
	else if (isDowned and !isLanded) {
		downedAnimCount++;
		sprite.move(0, 5 * SCREEN_DIFF);
		sf::Rect<float> spriteRect = sprite.getGlobalBounds();
		if (spriteRect.top + spriteRect.height >= SCREEN_SIZE[1] - 10 * SCREEN_DIFF) land();
		if (downedAnimCount == 15) {
			downedAnimCount = 0;
			sprite.scale(-1, 1);
		}
	}
	else {
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
		if (posRect.left + posRect.width <= 0 or posRect.left > SCREEN_SIZE[0]) return false;
		if (goRight) sprite.move(SCREEN_DIFF, 0);
		else sprite.move(-SCREEN_DIFF, 0);
	}

	window.draw(sprite);
	return true;
}

void Paratrooper::land() {
	isLanded = true;
	goRight = rand()%2;
	sprite.setRotation(-30 + rand()%60);
	sprite.setTexture(PARATROOPERS[type][1]);
}

void Paratrooper::down() {
	isDowned = true;
	sprite.setTexture(PARATROOPERS[type][1]);
}

sf::Rect<float> Paratrooper::getRect() {
	return sprite.getGlobalBounds();
}