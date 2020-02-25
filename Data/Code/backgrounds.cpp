#include "main.hpp"

extern sf::Texture BG_OBJECTS[2][4];
extern int SCREEN_SIZE[2];
extern float SCREEN_DIFF;

BgObject::BgObject() {
	type = rand() % 3;
	bgSprite.setTexture(BG_OBJECTS[type][0]);
	bgSprite.setScale(4 * SCREEN_DIFF, 4 * SCREEN_DIFF);
	sf::Rect<float> tempRect = bgSprite.getGlobalBounds();
	bgSprite.setPosition(10 + rand()%int(SCREEN_SIZE[0] - SCREEN_DIFF * 20.f - tempRect.width), SCREEN_SIZE[1] - SCREEN_DIFF * 5 - tempRect.height - rand() % 15);
	tempRect = bgSprite.getGlobalBounds();
	isBurned = false;
	animTimer = 0;
	peopleMade = false;
}

void BgObject::draw(sf::RenderWindow *window) {
	if (isBurned) {
		animTimer++;
		if (animTimer > 24) animTimer = 0;
		else if (animTimer % 8 == 0) {
			bgSprite.setTexture(BG_OBJECTS[type][(animTimer + 1) / 8]);
		}
	}
	window->draw(bgSprite);
}

void BgObject::burn(std::vector<People> &people) {
	isBurned = true;
	if (type == 1 and !peopleMade) {
		int countOfPeople = rand()%3;
		for (int i = 0; i <= countOfPeople; i++) {
			sf::Rect<float> tempRect = bgSprite.getGlobalBounds();
			people.push_back(People(\
				tempRect.left + tempRect.width / 2 - 5 + rand()%10,
				tempRect.top + tempRect.height - 10 - 5 + rand()%10
			));
		}
		peopleMade = true;
	}
}

sf::Rect<float> BgObject::getRect() {
	return bgSprite.getGlobalBounds();
}

int BgObject::getType() {
	return type;
}