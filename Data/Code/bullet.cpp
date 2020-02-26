#include "main.hpp"

extern int SCREEN_SIZE[2];
extern float SCREEN_DIFF;
extern sf::Texture BULLET;

Bullet::Bullet(int x, int y, int planeAngle, unsigned int planeId) {
	bulletSprite.setTexture(BULLET);
	bulletSprite.setPosition(x, y);
	bulletSprite.setScale(2.5 * SCREEN_DIFF, 2.5 * SCREEN_DIFF);
	angle = planeAngle + 90;
	speed = 7;
	id = planeId;
}

bool Bullet::update( std::vector<BgObject> &bgObjects, std::vector<People> &people, std::vector<Paratrooper> &paratroopers) {
	bulletSprite.move(
		float(speed * SCREEN_DIFF * std::sin(angle * PI / 180)),
	   -float(speed * SCREEN_DIFF * std::cos(angle * PI / 180))
	);

	sf::Rect<float> bulletRect = bulletSprite.getGlobalBounds();
	if (bulletRect.left < -10 * SCREEN_DIFF or 
		bulletRect.top < -10 * SCREEN_DIFF or 
		bulletRect.left + bulletRect.width > SCREEN_SIZE[0] or 
		bulletRect.top + bulletRect.height > SCREEN_SIZE[1]
	) return false;

	for (auto &bgObject: bgObjects)
		if (bulletRect.intersects(bgObject.getRect())) {
			bgObject.burn(people);
		}

	for (auto &paratrooper : paratroopers)
		if (bulletRect.intersects(paratrooper.getRect())) {
			paratrooper.down();
		}

	return  true;
}

void Bullet::draw(sf::RenderWindow &window) {
	window.draw(bulletSprite);
}

sf::Rect<float> Bullet::getRect() {
	return bulletSprite.getGlobalBounds();
}