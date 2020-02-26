#include "Data/Code/main.hpp"

sf::Texture PLANES_IMAGES[4];
sf::Texture BULLET;
sf::Texture BACKGROUND;
sf::Texture EXPLOSIONS[8];
sf::Texture BG_OBJECTS[3][4];
sf::Texture PEOPLE[4];
sf::Texture PARATROOPERS[4][2];
sf::Texture CLOUDS[3];
sf::Texture BALLOONS[3];

sf::Font mainFont;

sf::RenderWindow window;

int SCREEN_SIZE[2];
float SCREEN_DIFF;

int main(int argc, char**argv) {
	load();
	singlePlayer();

	return 0;
}