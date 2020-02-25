extern int SCREEN_SIZE[2];

bool updateNPC(Plane enemy, Plane &me, std::vector<Bullet> &bullets, std::vector<People> &p, std::vector<BgObject> &bgo) {
	int rightSum = 0 , leftSum = 0;
	bool turnLeft = false, turnRight = false, shoot = false;
	if (!me.isDead()) {
		int angle;
		if (!enemy.isDead())
			angle = std::atan2(me.getRect().left - enemy.getRect().left, me.getRect().top - enemy.getRect().top) / PI * 180;
		else
			angle = std::atan2(me.getRect().left - SCREEN_SIZE[0] / 2, me.getRect().top - SCREEN_SIZE[1] / 2) / PI * 180;
		angle = angle < 0 ? 360 + angle : angle;
		angle = -angle - 90;
		while (angle < 0) angle += 360;
		if (std::abs(angle - me.getRotation()) < 15) shoot = true;
		if (me.getRotation() < angle) rightSum += 10;
		else if (me.getRotation() > angle) leftSum += 10;
	}
	if (leftSum > rightSum)  turnLeft = true;
	else if (leftSum < rightSum) turnRight = true;

	if (shoot) me.shoot(bullets, &BULLET);
	return me.update(turnLeft, turnRight, bullets, bgo, p, false);
}