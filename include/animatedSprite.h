#include <SFML/Graphics.hpp>

class AnimatedSprite: public sf::Sprite
{
public:
	AnimatedSprite(const sf::Texture&, unsigned); // constructor

	void animate(); // Function to maniuplate opacity to simulate animation
private:
	int patricksIdea[10];
	bool flicker;
	unsigned index;
	sf::Texture t;
	sf::Clock timer;
};
