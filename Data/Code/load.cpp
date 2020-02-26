#include "main.hpp"

extern sf::Texture PLANES_IMAGES[4];
extern sf::Texture BULLET;
extern sf::Texture BACKGROUND;
extern sf::Texture EXPLOSIONS[8];
extern sf::Texture BG_OBJECTS[3][4];
extern sf::Texture PEOPLE[4];
extern sf::Texture PARATROOPERS[4][2];
extern sf::Texture CLOUDS[3];
extern sf::Texture BALLOONS[3];

extern sf::Font mainFont;

extern sf::RenderWindow window;
extern int SCREEN_SIZE[2];
extern float SCREEN_DIFF;

void loadImages() {
	BULLET.loadFromFile("Data/Images/bullets/bullet.png");
	BACKGROUND.loadFromFile("Data/Images/background/background.png");

	for (int i = 0; i < 4; i++)
		PLANES_IMAGES[i].loadFromFile("Data/Images/planes/" + std::to_string(i) + ".png");

	for (int i = 0; i < 8; i++)
		EXPLOSIONS[i].loadFromFile("Data/Images/explosions/" + std::to_string(i) + ".png");

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 4; j++)
			BG_OBJECTS[i][j].loadFromFile("Data/Images/background/onLand/" + std::to_string(i) + '/' + std::to_string(j) + ".png");

	for (int i = 0; i < 4; i++)
		PEOPLE[i].loadFromFile("Data/Images/people/" + std::to_string(i) + ".png");

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 2; j++)
			PARATROOPERS[i][j].loadFromFile("Data/Images/paratroopers/" + std::to_string(i) + '/' + std::to_string(j) + ".png");

	for (int i = 0; i < 3; i++)
		CLOUDS[i].loadFromFile("Data/Images/background/clouds/" + std::to_string(i) + ".png");

	for (int i = 0; i < 3; i++)
		BALLOONS[i].loadFromFile("Data/Images/background/balloons/" + std::to_string(i) + ".png");
};

void loadFonts() {
	mainFont.loadFromFile("Data/Fonts/mainFont.ttf");
};

void load() {
	std::srand(std::time(NULL));
	loadImages();
	loadFonts();

	SCREEN_SIZE[0] = sf::VideoMode::getDesktopMode().width;
	SCREEN_SIZE[1] = sf::VideoMode::getDesktopMode().height;
	SCREEN_DIFF = std::min(float((float)SCREEN_SIZE[0] / 1366), float((float)SCREEN_SIZE[1]) / 768);

	window.create(sf::VideoMode::getDesktopMode(), "PLANES", sf::Style::Fullscreen);
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);

	sf::Image ICON;
	ICON.loadFromFile("Data/Images/icon.png");
	window.setIcon(36, 36, ICON.getPixelsPtr());
};