#include "main.hpp"

extern sf::Texture PLANES_IMAGES[4];
extern int SCREEN_SIZE[2];
extern float SCREEN_DIFF;

Plane::Plane(int x, int y, int angle, int colorNum) {
	planeSprite.setTexture(PLANES_IMAGES[colorNum]);
	planeSprite.setOrigin(planeSprite.getGlobalBounds().width / 2, planeSprite.getGlobalBounds().height / 2);
	planeSprite.scale(4 * SCREEN_DIFF, 4 * SCREEN_DIFF);
	planeSprite.setPosition(x * SCREEN_DIFF, y * SCREEN_DIFF);
	planeSprite.rotate(angle);

	type = colorNum;
	startOptions = {x * SCREEN_DIFF, y * SCREEN_DIFF, float(angle)};
	speed = 2;
	deadMan = isInvisible = false;
	deadTimer = shootTimer = 0;
	id = rand()%10000;
	lookToRight = (angle > 270 or angle < 90) ? true:false;
	if (!lookToRight) planeSprite.scale(1, -1);
	forceTimer = invulnerabilityCounter = 0;
}

bool Plane::update(bool turnLeft, bool turnRight, std::vector<Bullet> &bullets, std::vector<BgObject>& bgObjects, std::vector<People> &people, bool isShiftPressed, bool isGodMode, bool isMinigun) {
	if (invulnerabilityCounter > 0) invulnerabilityCounter--;
	if (invulnerabilityCounter % 10 == 0 and invulnerabilityCounter != 0) {
		if (isInvisible) planeSprite.setColor(sf::Color(255, 255, 255, 255));
		else planeSprite.setColor(sf::Color(255, 255, 255, 120));
		isInvisible = !isInvisible;
	}
	if (isInvisible and invulnerabilityCounter == 0) {
		planeSprite.setColor(sf::Color(255, 255, 255, 255));
		isInvisible = false;
	}

	if (deadTimer > 0 and isDead()) planeSprite.setPosition(-100 * SCREEN_DIFF, -100 * SCREEN_DIFF);
	if (turnLeft and !turnRight) planeSprite.rotate(-2);
	if (turnRight and !turnLeft) planeSprite.rotate(2);

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
		if (forceTimer == 120 and !isGodMode) {
			die();
			causeOfDeath = 2;
			return false;
		}
		moveSpeed = float(speed) * 2;
	}
	else if (isShiftPressed && forceTimer > 0) forceTimer--;
	planeSprite.move(
		float(moveSpeed * SCREEN_DIFF * std::sin(planeRotation * PI / 180)),
	   -float(moveSpeed * SCREEN_DIFF * std::cos(planeRotation * PI / 180))
	);

	sf::Rect<float> planeRect = planeSprite.getGlobalBounds();
	for (int bull = 0; bull < bullets.size(); bull++) {
		sf::Rect<float> bulletRect = bullets[bull].getRect();
		if (planeRect.intersects(bulletRect) and id != bullets[bull].id and invulnerabilityCounter == 0 and !isGodMode) {
			bullets.erase(bullets.begin() + bull);
			die();
			causeOfDeath = 1;
			return false;
		}
	}
	for (auto &bgObject : bgObjects) {
		sf::Rect<float> tempRect = bgObject.getRect();
		if (planeRect.intersects(tempRect) and !isGodMode) {
			bgObject.burn(people);
			sf::Rect<float> expRect(planeRect.left - 25, planeRect.top - 25, planeRect.width + 50, planeRect.height + 50);
			for (auto &bgO : bgObjects) {
				if (expRect.intersects(bgO.getRect())) bgO.burn(people);
			}
			die();
			causeOfDeath = 2;
			return false;
		}
	}

	if ((planeRect.left < 0 or planeRect.top < 0 or planeRect.left + planeRect.width > SCREEN_SIZE[0] or planeRect.top + planeRect.height > SCREEN_SIZE[1]) and !isDead() ) {
		die();
		causeOfDeath = 2;
		return false;
	}

	if (isDead()) {
		deadTimer++;
		if (deadTimer >= 120) reset();
	}

	if (shootTimer > 0) shootTimer--;
	if (isMinigun) shootTimer = 0;

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
	deadMan = isInvisible = false;
	speed = 2;
	deadTimer = shootTimer = forceTimer = 0;
	invulnerabilityCounter = 90;
	planeSprite.setColor(sf::Color(255, 255, 255, 255));
}

sf::Rect<float> Plane::getRect() {
	return planeSprite.getGlobalBounds();
}

void Plane::shoot(std::vector<Bullet> &bullets) {
	if (shootTimer <= 0 and !isDead()) {
		sf::Rect<float> tempRect = planeSprite.getGlobalBounds();
		bullets.push_back(Bullet(tempRect.left + tempRect.width / 2, tempRect.top + tempRect.height / 2, planeSprite.getRotation(), id));
		shootTimer = 40;
	}
}

int Plane::getType() {
	return type;
}

int Plane::getRotation() {
	return planeSprite.getRotation();
}

int Plane::getCauseOfDeath() {
	return causeOfDeath;
}