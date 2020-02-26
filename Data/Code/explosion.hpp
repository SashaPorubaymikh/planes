#ifndef EXPLOSION_HPP
#define EXPLOSION_HPP

class Explosion {
	public:
		Explosion(sf::Rect<float>);
		bool draw(sf::RenderWindow&);
	private:
		sf::Sprite explosionSprite;
		short int timer;
};

#endif