#include "main.hpp"

extern int SCREEN_SIZE[2];

bool updateNPC(Plane enemy, Plane &npc, std::vector<Bullet> &bullets, std::vector<People> &people, std::vector<BgObject> &bgObjects) {
	int rightSum = 0 , leftSum = 0;
	bool turnLeft = false, turnRight = false, shoot = false;
	if (!npc.isDead()) {
		int angle;
		if (!enemy.isDead())
			angle = std::atan2(npc.getRect().left - enemy.getRect().left, npc.getRect().top - enemy.getRect().top) / PI * 180;
		else
			angle = std::atan2(npc.getRect().left - SCREEN_SIZE[0] / 2, npc.getRect().top - SCREEN_SIZE[1] / 2) / PI * 180;
		angle = angle < 0 ? 360 + angle : angle;
		angle = -angle - 90;
		while (angle < 0) angle += 360;
		if (std::abs(angle - npc.getRotation()) < 15) shoot = true;
		if (npc.getRotation() < angle) rightSum += 10;
		else if (npc.getRotation() > angle) leftSum += 10;
	}
	if (leftSum > rightSum)  turnLeft = true;
	else if (leftSum < rightSum) turnRight = true;

	if (shoot) npc.shoot(bullets);
	return npc.update(turnLeft, turnRight, bullets, bgObjects, people, false);
}