#include "main.hpp"

extern sf::RenderWindow window;
extern int SCREEN_SIZE[2];
extern float SCREEN_DIFF;
extern sf::Font mainFont;
extern sf::Texture BACKGROUND;

void singlePlayer() {
	sf::Sprite backgroundSprite;
	float maxScreenDiffForBG = std::max(float(SCREEN_SIZE[0]) / 1366, float(SCREEN_SIZE[1]) / 768);
	backgroundSprite.setTexture(BACKGROUND);
	backgroundSprite.setScale(2.5 * maxScreenDiffForBG, 2.5 * maxScreenDiffForBG);

	std::vector<Bullet> bullets;
	std::vector<Explosion> explosions;
	std::vector<People> people;
	std::vector<Paratrooper> paratroopers;
	std::array<Cloud, 5> clouds;
	std::array<Balloon, 1> balloons;
	std::vector<BgObject> bgObjects;

	int countOfBgObjects = 40 + rand()%20;
	for (int bgObj = 0; bgObj <= countOfBgObjects; bgObj++) {
		bgObjects.push_back(BgObject());
	}
	std::sort(bgObjects.begin(), bgObjects.end(), [](BgObject a, BgObject b) {
		return (a.getRect().top + a.getRect().height) < (b.getRect().top + b.getRect().height);
	});

	Plane player(40, 40, 0, 0);
	Plane enemy(1320, 40, 180, 1);


	bool turnLeft = false, turnRight = false, spacePressed = false;

	unsigned int playerPoints = 0, botPoints = 0;

	std::string cheatString = "";
	bool isGodMode = false, isMinigun = false;

	while(window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::KeyPressed)
				switch(event.key.code) {
					case sf::Keyboard::Delete:
						player.die();
						explosions.push_back(Explosion(player.getRect()));
						paratroopers.push_back(Paratrooper(player.getRect().left, player.getRect().top, player.getType()));
						if (playerPoints > 0) playerPoints -= 1;
						break;
					case sf::Keyboard::Escape:
						window.close();
						break;
				}
			if (event.type == sf::Event::TextEntered)
				cheatString += char(event.text.unicode);
		}

		checkForCheat(cheatString, backgroundSprite, player, enemy, isGodMode, isMinigun);

		window.clear(sf::Color::Black);

		window.draw(backgroundSprite);
		for (auto &balloon: balloons) 
			balloon.draw(window);

		if (!player.update(
			sf::Keyboard::isKeyPressed(sf::Keyboard::Left), 
			sf::Keyboard::isKeyPressed(sf::Keyboard::Right), 
			bullets, 
			bgObjects, 
			people, 
			sf::Keyboard::isKeyPressed(sf::Keyboard::LShift),
			isGodMode=isGodMode,
			isMinigun=isMinigun)
		) {
			explosions.push_back(Explosion(player.getRect()));
			paratroopers.push_back(Paratrooper(player.getRect().left, player.getRect().top, player.getType()));
			if (player.getCauseOfDeath() == 1)
				botPoints++;
			else if (player.getCauseOfDeath() == 2 and playerPoints > 0)
				playerPoints -= 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) player.shoot(bullets);
		player.draw(window);

		if (!updateNPC(player, enemy, bullets, people, bgObjects)) {
			explosions.push_back(Explosion(enemy.getRect()));
			paratroopers.push_back(Paratrooper(enemy.getRect().left, enemy.getRect().top, enemy.getType()));
			if (enemy.getCauseOfDeath() == 1)
				playerPoints++;
			else if (enemy.getCauseOfDeath() == 2 and botPoints > 0)
				botPoints -= 1;
		}
		enemy.draw(window);

		for (int bullet = 0; bullet < bullets.size(); bullet++) {
			if (!bullets[bullet].update(bgObjects, people, paratroopers))
				bullets.erase(bullets.begin() + bullet);
			else bullets[bullet].draw(window);
		}

		for (int exp = 0; exp < explosions.size(); exp++)
			if (!explosions[exp].draw(window))
				explosions.erase(explosions.begin() + exp);

		for (auto &bgObject : bgObjects) 
			bgObject.draw(window);
		
		for (int person = 0; person < people.size(); person++)
			if (!people[person].draw(window))
				people.erase(people.begin() + person);

		for (int paratrooper = 0; paratrooper < paratroopers.size(); paratrooper++)
			if (!paratroopers[paratrooper].draw(window))
				paratroopers.erase(paratroopers.begin() + paratrooper);

		for (auto &cloud : clouds) 
			cloud.draw(window);

		sf::Text pointsText;
		pointsText.setFont(mainFont);
		pointsText.setString(std::to_string(playerPoints) + " | " + std::to_string(botPoints));
		pointsText.setCharacterSize(20 * SCREEN_DIFF);
		pointsText.setFillColor(sf::Color::Black);
		sf::Rect<float> textRect = pointsText.getGlobalBounds();
		pointsText.setPosition(float(SCREEN_SIZE[0]) / 2 - textRect.width / 2 + 2*SCREEN_DIFF, 20*SCREEN_DIFF + 2*SCREEN_DIFF);
		window.draw(pointsText);
		pointsText.setFillColor(sf::Color(200, 200, 200));
		textRect = pointsText.getGlobalBounds();
		pointsText.setPosition(float(SCREEN_SIZE[0]) / 2 - textRect.width / 2, 20*SCREEN_DIFF);
		window.draw(pointsText);
		

		window.display();
	}
};

void checkForCheat(std::string &str, sf::Sprite &backgroundSprite, Plane &player, Plane &enemy, bool &isGodMode, bool &isMinigun) {
	if (str.size() > 7 and str.substr(str.size() - 7) == "Toughie") {
		isGodMode = !isGodMode;
		str.clear();
	}
	if (str.size() > 6 and str.substr(str.size() - 6) == "Arnold") {
		isMinigun = !isMinigun;
		str.clear();
	}
}