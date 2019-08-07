#include <SFML/Graphics.hpp>
#include "../include/screen.h"

Screen::Screen(sf::RenderWindow& w)
{
    this->screenSize =  sf::Vector2f(w.getSize());
    this->margin = sf::Vector2f(this->screenSize.x * 1/20, this->screenSize.y * 1/20);
    this->corner.loadFromFile("assets/corner.png");

    this->create(this->screenSize.x, this->screenSize.y);
    this->initialize();

    for(size_t i = 0; i < 4; i++)
    {
        this->cornerSprites.push_back(AnimatedSprite(this->corner, i));
        setSpriteOriginToCenter(this->cornerSprites[i]);
        this->cornerSprites[i].rotate(90 * i);
    }

    this->cornerSprites[0].setPosition( corner.getSize().x / 2 + margin.x,
						                corner.getSize().y / 2 + margin.y);

    this->cornerSprites[1].setPosition( screenSize.x - (corner.getSize().x / 2 + margin.x),
                                        corner.getSize().y / 2 + margin.y);

    this->cornerSprites[2].setPosition( screenSize.x - (corner.getSize().x / 2 + margin.x),
							            screenSize.y - (corner.getSize().y / 2 + margin.y));

    this->cornerSprites[3].setPosition( corner.getSize().x / 2 + margin.x,
							            screenSize.y - (corner.getSize().y / 2 + margin.y));
}

void Screen::animate()
{
    for (auto i : this->cornerSprites)
        i.animate();
}

void Screen::drawCorners()
{
    for (auto i : this->cornerSprites)
        this->draw(i);
}

void Screen::setSpriteOriginToCenter(AnimatedSprite& spr)
{
	/* In SFML, objects have an origin that act as the center of all transformations, such as
	 * rotation and position. The default value is the top left corner of said object
	 * (essetentially 0,0 in its local coordinate space). I find centering the origin
	 * makes transformations much easier thus this function.
	 */

	sf::FloatRect bounds = spr.getLocalBounds();

	spr.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
}
