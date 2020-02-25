#ifndef PLANE_HPP
#define PLANE_HPP

#include "bullet.hpp"
#include "backgrounds.hpp"
#include "people.hpp"

class Plane {
	public:
		Plane(int, int, int, int);
		bool update(bool, bool, std::vector<Bullet>&, std::vector<BgObject>&, std::vector<People>&, bool);
		void draw(sf::RenderWindow&);
		void die();
		bool isDead();
		void reset();
		sf::Rect<float> getRect();
		void shoot(std::vector<Bullet>&, sf::Texture*);
		int getType();
		int getRotation();

		unsigned int id;

	private:
		sf::Sprite planeSprite;
		int speed;
		bool deadMan;
		std::array<float, 3> startOptions;
		short int deadTimer;
		short int shootTimer;
		int type;
		bool lookToRight;
		float yFlip;
		int forceTimer;
};

#endif