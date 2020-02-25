class Cloud {
	public:
		Cloud();
		void reset();
		void draw(sf::RenderWindow*);
	private:
		sf::Sprite sprite;
		float speed;
};