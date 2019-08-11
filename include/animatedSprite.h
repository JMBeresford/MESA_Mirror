#include <SFML/Graphics.hpp>

class AnimatedSprite: public sf::Sprite
{
public:
	AnimatedSprite(const sf::Texture&, unsigned); // ctor

	void animate(); // Function to manipulate opacity to simulate animation
private:
	int patricksIdea[10]; // array of random nums 5-30 to be used as intervals for animation
	bool flicker; // flag for animation
	unsigned index; // used to index the above array
	sf::Clock timer; // used for the interval
};
