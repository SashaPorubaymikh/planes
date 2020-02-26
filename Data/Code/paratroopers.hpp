#ifndef PARATROOPER_HPP
#define PARATROOPER_HPP

class Paratrooper {
	public:
		Paratrooper(int, int, int);
		bool draw(sf::RenderWindow&);
		void land();
		void down();
		sf::Rect<float> getRect();
	private:
		sf::Sprite sprite;
		short int type;
		bool isLanded;
		bool goRight;
		bool rotateRight;
		bool isDowned;
		short int downedAnimCount;
};

#endif