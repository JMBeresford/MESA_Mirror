#include <SFML/Graphics.hpp>

class AnimatedSprite: public sf::Sprite
{
public:
	AnimatedSprite();
	AnimatedSprite(const sf::Texture&);
	int getOpacity(); // returns current opacity
	void setOpacity(int); // sets new opacityc

	void setOriginToCenter(); // Sets the origin of the shape to its center
	void animate(); // Function to maniuplate opacity to simulate animation
private:
	bool fade, flicker;
	int opacity = 255;
	sf::Texture t;
};
