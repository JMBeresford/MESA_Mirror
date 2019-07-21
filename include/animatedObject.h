#include <SFML/Graphics.hpp>

class AnimatedRect: public sf::RectangleShape
{
public:
	AnimatedRect(const sf::Vector2f& size=sf::Vector2f(0,0));
	int getOpacity(); // returns current opacity
	void setOpacity(int); // sets new opacityc

	void setOriginToCenter(); // Sets the origin of the shape to its center
	void animate(); // Function to maniuplate opacity to simulate animation
private:
	bool fade, flicker;
	int opacity = 255;
};


class AnimatedCircle: public sf::CircleShape
{
public:
	AnimatedCircle(const sf::Vector2f& size=sf::Vector2f(0,0));
	int getOpacity(); // returns current opacity
	void setOpacity(int); // sets new opacityc

	void setOriginToCenter(); // Sets the origin of the shape to its center
	void animate(); // Function to maniuplate opacity to simulate animation
private:
	bool fade, flicker;
	int opacity = 255;
};


class AnimatedConvex: public sf::ConvexShape
{
public:
	AnimatedConvex(const sf::Vector2f& size=sf::Vector2f(0,0));
	int getOpacity(); // returns current opacity
	void setOpacity(int); // sets new opacityc

	void setOriginToCenter(); // Sets the origin of the shape to its center
	void animate(); // Function to maniuplate opacity to simulate animation
private:
	bool fade, flicker;
	int opacity = 255;
};


class AnimatedText: public sf::Text
{
public:
	AnimatedText();
	int getOpacity(); // returns current opacity
	void setOpacity(int); // sets new opacityc

	void setOriginToCenter(); // Sets the origin of the shape to its center
	void animate(); // Function to maniuplate opacity to simulate animation
private:
	bool fade, flicker;
	int opacity = 255;
};

