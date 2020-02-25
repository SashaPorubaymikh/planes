#ifndef BULLET_HPP
#define BULLET_HPP

#include "backgrounds.hpp"
#include "people.hpp"
#include "paratroopers.hpp"

class Bullet {
	public:
		unsigned int id;

		Bullet(int, int, int, sf::Texture*, unsigned int);
		bool update( std::vector<BgObject>&, std::vector<People>&, std::vector<Paratrooper>&);
		void draw(sf::RenderWindow*);
		sf::Rect<float> getRect();
	private:
		sf::Sprite bulletSprite;
		short int angle;
		short int speed;
};

#endif