#include "main.hpp"

extern sf::Texture PLANES_IMAGES[4];
extern int SCREEN_SIZE[2];
extern float SCREEN_DIFF;

Plane::Plane(int x, int y, int angle, int colorNum) {
	planeSprite.setTexture(PLANES_IMAGES[colorNum]);
	type = colorNum;
	planeSprite.setOrigin(planeSprite.getGlobalBounds().width / 2, planeSprite.getGlobalBounds().height / 2);
	planeSprite.scale(4 * SCREEN_DIFF, 4 * SCREEN_DIFF);
	planeSprite.setPosition(x * SCREEN_DIFF, y * SCREEN_DIFF);
	planeSprite.rotate(angle);

	startOptions = {x * SCREEN_DIFF, y * SCREEN_DIFF, angle};
	speed = 2;
	deadMan = false;
	deadTimer = 0;
	shootTimer = 0;
	id = rand()%10000;
	lookToRight = (angle > 270 or angle < 90) ? true:false;
	if (!lookToRight) planeSprite.scale(1, -1);
	yFlip = 1;
	forceTimer = 0;
}

bool Plane::update(bool turnLeft, bool turnRight, std::vector<Bullet> &bullets, std::vector<BgObject>& bgObjects, std::vector<People> &people, bool isShiftPressed) {
	if (deadTimer > 0 and isDead()) planeSprite.setPosition(-100 * SCREEN_DIFF, -100 * SCREEN_DIFF);
	if (turnLeft and !turnRight) planeSprite.rotate(-2);
	if (turnRight and !turnLeft) planeSprite.rotate(2);
	if ((turnRight and turnLeft) or (!turnLeft and !turnRight)) {
		short int planeRotation = planeSprite.getRotation();
		if ((planeRotation >= 270 or planeRotation < 90) and std::abs(90 - planeRotation) > 1) planeSprite.rotate(0);
		else if ((planeRotation < 270 or planeRotation > 90) and std::abs(90 - planeRotation) > 1) planeSprite.rotate(-0);
	}
	if ((lookToRight and planeSprite.getRotation() > 105 and planeSprite.getRotation() < 255)) {
		lookToRight = false;
		planeSprite.scale(1, -1);
	}
	else if ((!lookToRight and (planeSprite.getRotation() > 285 or planeSprite.getRotation() < 75))) {
		lookToRight = true;
		planeSprite.scale(1, -1);
	}

	short int planeRotation = planeSprite.getRotation() + 90;

	float moveSpeed = speed;
	if (isShiftPressed && !isDead()) {
		forceTimer++;
		if (forceTimer == 120) {
			die();
			return false;
		}
		moveSpeed = float(speed) * 2;
	}
	else if (isShiftPressed && forceTimer > 0) forceTimer--;
	planeSprite.move((float)(moveSpeed * SCREEN_DIFF * std::sin(planeRotation * PI / 180)), -(float)(moveSpeed * SCREEN_DIFF *std::cos(planeRotation * PI / 180)));

	sf::Rect<float> planeRect = planeSprite.getGlobalBounds();
	for (int bull = 0; bull < bullets.size(); bull++) {
		sf::Rect<float> bulletRect = bullets[bull].getRect();
		// std::cout << (id != bullets[bull].id) << std::endl;
		// std::cout << id << std::endl;
		// std::cout << (bullets[bull].id) << std::endl;
		// std::cout << std::endl;
		if (planeRect.intersects(bulletRect) and id != bullets[bull].id) {
			bullets.erase(bullets.begin() + bull);
			die();
			return false;
		}
	}
	for (auto &bgObject : bgObjects) {
		sf::Rect<float> tempRect = bgObject.getRect();
		if (planeRect.intersects(tempRect)) {
			bgObject.burn(people);
			sf::Rect<float> expRect(planeRect.left - 25, planeRect.top - 25, planeRect.width + 50, planeRect.height + 50);
			for (auto &bgO : bgObjects) {
				if (expRect.intersects(bgO.getRect())) bgO.burn(people);
			}
			die();
			return false;
		}
	}
	if ((planeRect.left < 0 or planeRect.top < 0 or planeRect.left + planeRect.width > SCREEN_SIZE[0] or planeRect.top + planeRect.height > SCREEN_SIZE[1]) and !isDead() ) {
		die();
		return false;
	}
	if (isDead()) {
		deadTimer++;
		if (deadTimer >= 120) reset();
	}

	if (shootTimer > 0) shootTimer--;

	return true;
}

void Plane::draw(sf::RenderWindow &window) {
	if (!isDead()) window.draw(planeSprite);
}

void Plane::die() {
	deadMan = true;
	deadTimer = 1;
}

bool Plane::isDead() {
	return deadMan;
}

void Plane::reset() {
	planeSprite.setRotation(startOptions[2]);
	planeSprite.setPosition(startOptions[0], startOptions[1]);
	deadMan = false;
	speed = 2;
	deadTimer = 0;
	shootTimer = 0;
	forceTimer = 0;
}

sf::Rect<float> Plane::getRect() {
	return planeSprite.getGlobalBounds();
}

void Plane::shoot(std::vector<Bullet> &bullets, sf::Texture *texture) {
	if (shootTimer <= 0 and !isDead()) {
		sf::Rect<float> tempRect = planeSprite.getGlobalBounds();
		bullets.push_back(Bullet(tempRect.left + tempRect.width / 2, tempRect.top + tempRect.height / 2, planeSprite.getRotation(), texture, id));
		shootTimer = 40;
	}
}

int Plane::getType() {
	return type;
}

int Plane::getRotation() {
	return planeSprite.getRotation();
}