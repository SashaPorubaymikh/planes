#include "npc.hpp"

extern sf::RenderWindow window;
extern int SCREEN_SIZE[2];
extern float SCREEN_DIFF;

bool Comp(BgObject a, BgObject b) {
	return (a.getRect().top + a.getRect().height) < (b.getRect().top + b.getRect().height);
}

void mainGame() {
	sf::Sprite backgroundSprite;
	float maxScreenDiffForBG = std::max(float((float)SCREEN_SIZE[0] / 1366), float((float)SCREEN_SIZE[1]) / 768);
	backgroundSprite.setTexture(BACKGROUND);
	backgroundSprite.setScale(5 * maxScreenDiffForBG, 5 * maxScreenDiffForBG);

	std::vector<BgObject> bgObjects;
	int countOfBgObjects = 40 + rand()%20;
	for (int bgObj = 0; bgObj <= countOfBgObjects; bgObj++) {
		bgObjects.push_back(BgObject());
	}
	std::sort(bgObjects.begin(), bgObjects.end(), [](BgObject a, BgObject b) {
		return (a.getRect().top + a.getRect().height) < (b.getRect().top + b.getRect().height);
	});

	std::vector<Bullet> bullets;
	std::vector<Explosion> explosions;
	std::vector<People> people;
	std::vector<Paratrooper> paratroopers;
	std::array<Cloud, 5> clouds;
	std::array<Balloon, 5> balloons;

	Plane player(40, 40, 0, 0); // 4th parameter - number of plane's color
	Plane enemy(1320, 40, 180, 1);


	bool turnLeft = false, turnRight = false, spacePressed = false;

	while(window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::KeyPressed)
				switch(event.key.code) {
					case sf::Keyboard::Left:
						turnLeft = true;
						break;
					case sf::Keyboard::Right:
						turnRight = true;
						break;
					case sf::Keyboard::Delete:
						player.die();
						explosions.push_back(Explosion(player.getRect()));
						paratroopers.push_back(Paratrooper(player.getRect().left, player.getRect().top, player.getType()));
						break;
					case sf::Keyboard::Space:
						spacePressed = true;
						break;
					case sf::Keyboard::Escape:
						window.close();
						break;
					case sf::Keyboard::F1:
						window.setFramerateLimit(1);
						break;
				}
			if (event.type == sf::Event::KeyReleased)
				switch(event.key.code) {
					case sf::Keyboard::Left:
						turnLeft = false;
						break;
					case sf::Keyboard::Right:
						turnRight = false;
						break;
					case sf::Keyboard::Space:
						spacePressed = false;
						break;
					case sf::Keyboard::F1:
						window.setFramerateLimit(60);
						break;
				}
		}

		if (spacePressed) player.shoot(bullets, &BULLET);

		window.clear(sf::Color::Black);
		window.draw(backgroundSprite);
		for (auto &balloon: balloons) balloon.draw(&window);

		if (!player.update(turnLeft, turnRight, bullets, bgObjects, people, sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))) {
			explosions.push_back(Explosion(player.getRect()));
			paratroopers.push_back(Paratrooper(player.getRect().left, player.getRect().top, player.getType()));
		}
		player.draw(window);

		if (!updateNPC(player, enemy, bullets, people, bgObjects)) {
			explosions.push_back(Explosion(enemy.getRect()));
			paratroopers.push_back(Paratrooper(enemy.getRect().left, enemy.getRect().top, enemy.getType()));
		}
		enemy.draw(window);

		for (int bullet = 0; bullet < bullets.size(); bullet++) {
			if (!bullets[bullet].update(bgObjects, people, paratroopers))
				bullets.erase(bullets.begin() + bullet);
			else bullets[bullet].draw(&window);
		}

		for (int exp = 0; exp < explosions.size(); exp++)
			if (!explosions[exp].draw(&window))
				explosions.erase(explosions.begin() + exp);

		for (auto &bgObj : bgObjects) 
			bgObj.draw(&window);
		
		for (int person = 0; person < people.size(); person++)
			if (!people[person].draw(&window)) {
				people.erase(people.begin() + person);
			}

		for (int paratrooper = 0; paratrooper < paratroopers.size(); paratrooper++)
			if (!paratroopers[paratrooper].draw(&window))
				paratroopers.erase(paratroopers.begin() + paratrooper);

		for (auto &cloud : clouds) cloud.draw(&window);
		

		window.display();
	}
}