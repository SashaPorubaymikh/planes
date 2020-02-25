#ifndef PROPLE_HPP
#define PROPLE_HPP

class People {
	public:
		People(int, int);
		bool draw(sf::RenderWindow*);
	private:
		sf::Sprite sprite;
		short int angle;
		int animTimer;
		bool rotateRight;
		bool goRight;
		float speed;
};

#endif