#include <SFML/Graphics.hpp>
#include "screen.h"

Screen::Screen(sf::RenderWindow& w)
{
    /*
    This class creates an object that contains 4 'AnimatedSprite' objects that display
    the corner images seen in the program. It handles the instantiation of said Sprites
    allowing collaborators to use them in their 'screens' or 'menus' without having to
    fuss over doing all that legwork again. 
    */
    this->screenSize =  sf::Vector2f(w.getSize());

    // We create this margin so as to keep the corners slightly off the edge of screen
    this->margin = sf::Vector2f(this->screenSize.x * 1/20, this->screenSize.y * 1/20);
    this->corner.loadFromFile("assets/corner.png"); // Loads the texture with an image

    // Creates the actual render space
    this->create(this->screenSize.x, this->screenSize.y);

    // This pushes 4 AnimatedSprites into a vector
    for(size_t i = 0; i < 4; i++)
    {
        this->cornerSprites.push_back(AnimatedSprite(this->corner, i));
        setSpriteOriginToCenter(this->cornerSprites[i]); // Read the explanation below (line 56)
        
        // Each corner uses the same image for its texture, so we need to rotate them
        this->cornerSprites[i].rotate(90 * i);
    }

    /*
    The setPosition() function is explained well in the docs, so I would suggest reading
    those (and all other relevant references, tbh), but essentially this moves the origin
    of the given Sprite and moves it to the given coordinates. Remember the origin of
    each Sprite has been set to the center of each respective Sprite thus the expressions
    used for the coordinates.
    */
    this->cornerSprites[0].setPosition( corner.getSize().x / 2 + margin.x, // Top left
						                corner.getSize().y / 2 + margin.y);

    this->cornerSprites[1].setPosition( screenSize.x - (corner.getSize().x / 2 + margin.x),
                                        corner.getSize().y / 2 + margin.y); // top right

    // bottom right
    this->cornerSprites[2].setPosition( screenSize.x - (corner.getSize().x / 2 + margin.x),
							            screenSize.y - (corner.getSize().y / 2 + margin.y));
    // bottom left
    this->cornerSprites[3].setPosition( corner.getSize().x / 2 + margin.x,
							            screenSize.y - (corner.getSize().y / 2 + margin.y));
}

void Screen::animate()
{
    // Calls the animate function of the AnimatedSprite objects
    for (size_t i = 0; i < this->cornerSprites.size(); i++)
        this->cornerSprites[i].animate();
}

void Screen::drawCorners()
{
    // Draws the Sprites to 'this' RenderTexture,
    // remember this class inherits from sf::RenderTexture
    for (auto i : this->cornerSprites)
        this->draw(i);
}

void Screen::setSpriteOriginToCenter(AnimatedSprite& spr)
{
	/* In SFML, objects have an origin that act as the center of all transformations, such as
	 * rotation and position. The default value is the top left corner of said object
	 * (essetentially 0,0 in its local coordinate space). I find centering the origin
	 * makes transformations much easier, thus this function.
	 */

	sf::FloatRect bounds = spr.getLocalBounds();

	spr.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
}