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
		void shoot(std::vector<Bullet>&);
		int getType();
		int getRotation();
		int getCauseOfDeath();

		unsigned int id;

	private:
		sf::Sprite planeSprite;
		std::array<float, 3> startOptions;
		short int deadTimer, shootTimer;
		bool lookToRight, isInvisible, deadMan;
		int forceTimer, causeOfDeath, invulnerabilityCounter, type, speed;
};

#endif