extern sf::Texture PLANES_IMAGES[4];
extern sf::Texture BULLET;
extern sf::Texture BACKGROUND;
extern sf::Texture EXPLOSIONS[8];
extern sf::Texture BG_OBJECTS[3][4];
extern sf::Texture PEOPLE[4];
extern sf::Texture PARATROOPERS[4][2];
extern sf::Texture CLOUDS[3];
extern sf::Texture BALLOONS[3];

extern sf::RenderWindow window;
extern int SCREEN_SIZE[2];
extern float SCREEN_DIFF;

void loadImages() {
	PLANES_IMAGES[0].loadFromFile("Data/Images/planes/green_plane.png");
	PLANES_IMAGES[1].loadFromFile("Data/Images/planes/gray_plane.png");
	PLANES_IMAGES[2].loadFromFile("Data/Images/planes/blue_plane.png");
	PLANES_IMAGES[3].loadFromFile("Data/Images/planes/yellow_plane.png");

	BULLET.loadFromFile("Data/Images/bullets/bullet.png");
	BACKGROUND.loadFromFile("Data/Images/background/background.png");

	EXPLOSIONS[0].loadFromFile("Data/Images/explosions/1.png");
	EXPLOSIONS[1].loadFromFile("Data/Images/explosions/2.png");
	EXPLOSIONS[2].loadFromFile("Data/Images/explosions/3.png");
	EXPLOSIONS[3].loadFromFile("Data/Images/explosions/4.png");
	EXPLOSIONS[4].loadFromFile("Data/Images/explosions/5.png");
	EXPLOSIONS[5].loadFromFile("Data/Images/explosions/6.png");
	EXPLOSIONS[6].loadFromFile("Data/Images/explosions/7.png");
	EXPLOSIONS[7].loadFromFile("Data/Images/explosions/8.png");

	BG_OBJECTS[0][0].loadFromFile("Data/Images/background/fir-tree/0.png");
	BG_OBJECTS[0][1].loadFromFile("Data/Images/background/fir-tree/1.png");
	BG_OBJECTS[0][2].loadFromFile("Data/Images/background/fir-tree/2.png");
	BG_OBJECTS[0][3].loadFromFile("Data/Images/background/fir-tree/3.png");

	BG_OBJECTS[1][0].loadFromFile("Data/Images/background/house/0.png");
	BG_OBJECTS[1][1].loadFromFile("Data/Images/background/house/1.png");
	BG_OBJECTS[1][2].loadFromFile("Data/Images/background/house/2.png");
	BG_OBJECTS[1][3].loadFromFile("Data/Images/background/house/3.png");

	BG_OBJECTS[2][0].loadFromFile("Data/Images/background/oak/0.png");
	BG_OBJECTS[2][1].loadFromFile("Data/Images/background/oak/1.png");
	BG_OBJECTS[2][2].loadFromFile("Data/Images/background/oak/2.png");
	BG_OBJECTS[2][3].loadFromFile("Data/Images/background/oak/3.png");

	PEOPLE[0].loadFromFile("Data/Images/people/black-blue.png");
	PEOPLE[1].loadFromFile("Data/Images/people/black-green.png");
	PEOPLE[2].loadFromFile("Data/Images/people/white-blue.png");
	PEOPLE[3].loadFromFile("Data/Images/people/white-green.png");

	PARATROOPERS[0][0].loadFromFile("Data/Images/paratroopers/green/0.png");
	PARATROOPERS[1][0].loadFromFile("Data/Images/paratroopers/gray/0.png");
	PARATROOPERS[2][0].loadFromFile("Data/Images/paratroopers/blue/0.png");
	PARATROOPERS[3][0].loadFromFile("Data/Images/paratroopers/yellow/0.png");

	PARATROOPERS[0][1].loadFromFile("Data/Images/paratroopers/green/1.png");
	PARATROOPERS[1][1].loadFromFile("Data/Images/paratroopers/gray/1.png");
	PARATROOPERS[2][1].loadFromFile("Data/Images/paratroopers/blue/1.png");
	PARATROOPERS[3][1].loadFromFile("Data/Images/paratroopers/yellow/1.png");

	CLOUDS[0].loadFromFile("Data/Images/background/clouds/1.png");
	CLOUDS[1].loadFromFile("Data/Images/background/clouds/2.png");
	CLOUDS[2].loadFromFile("Data/Images/background/clouds/3.png");

	BALLOONS[0].loadFromFile("Data/Images/background/balloons/0.png");
	BALLOONS[1].loadFromFile("Data/Images/background/balloons/1.png");
	BALLOONS[2].loadFromFile("Data/Images/background/balloons/2.png");
}

void load() {
	std::srand(std::time(NULL));
	loadImages();

	SCREEN_SIZE[0] = sf::VideoMode::getDesktopMode().width;
	SCREEN_SIZE[1] = sf::VideoMode::getDesktopMode().height;
	SCREEN_DIFF = std::min(float((float)SCREEN_SIZE[0] / 1366), float((float)SCREEN_SIZE[1]) / 768);

	window.create(sf::VideoMode::getDesktopMode(), "PLANES", sf::Style::Fullscreen);
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);

	sf::Image ICON;
	ICON.loadFromFile("Data/Images/icon.png");
	window.setIcon(36, 36, ICON.getPixelsPtr());
}