#ifndef BACKGROUNDS_HPP
#define BACKGROUNDS_HPP

#include "people.hpp"

class BgObject {
	public:
		BgObject();
		void draw(sf::RenderWindow&);
		void burn(std::vector<People>&);
		sf::Rect<float> getRect();
		int getType();

	private:
		sf::Sprite bgSprite;
		short int type;
		bool isBurned;
		short int animTimer;
		bool peopleMade;
};

#endif