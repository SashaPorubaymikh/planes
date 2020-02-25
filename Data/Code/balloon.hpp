class Balloon {
	public:
		Balloon();
		void draw(sf::RenderWindow*);
		void reset();
	private:
		float speed;
		sf::Sprite sprite;
		bool goRight;
};