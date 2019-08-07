#include <SFML/Graphics.hpp>
#include "../include/splashScreen.h"

SplashScreen::SplashScreen(sf::RenderWindow& w)
{
    sf::Vector2f screenSize = sf::Vector2f(w.getSize());
    this->create(screenSize.x, screenSize.y);

    this->fnt.loadFromFile("assets/bladeRunner.ttf");
    this->enterText.setFont(this->fnt);
    this->mesaText.setFont(this->fnt);
    
    this->enterText.setString("Enter");
    this->mesaText.setString("Mesa");

    this->enterText.setCharacterSize(55);
    this->mesaText.setCharacterSize(55);

    this->ringTex.loadFromFile("assets/ring.png");
    this->shadowTex.loadFromFile("assets/ringShadow.png");

    this->ring.setTexture(ringTex);
    this->shadow.setTexture(shadowTex);

    setTextOriginToCenter(this->mesaText);
    setTextOriginToCenter(this->enterText);

    setSpriteOriginToCenter(this->ring);
    setSpriteOriginToCenter(this->shadow);

    this->ring.setPosition(sf::Vector2f(screenSize.x / 2.0f, screenSize.y / 2.0f));
    this->shadow.setPosition(sf::Vector2f(screenSize.x / 2.0f, screenSize.y / 2.0f));

    sf::FloatRect textSize = this->enterText.getLocalBounds();

    this->enterText.setPosition(sf::Vector2f(screenSize.x / 2.0f,
								screenSize.y / 2.0f - (textSize.height / 2 + 5)));

    this->mesaText.setPosition( sf::Vector2f(screenSize.x / 2.0f,
							    screenSize.y / 2.0f + (textSize.height / 2 + 5)));
}

void SplashScreen::drawRing()
{
    this->draw(ring);
    this->draw(shadow);
    this->draw(enterText);
    this->draw(mesaText);
}

void SplashScreen::rotateRing(int i)
{
    this->ring.rotate(i);
}

sf::FloatRect SplashScreen::getRingPos()
{
    return this->ring.getGlobalBounds();
}

void SplashScreen::setTextOriginToCenter(sf::Text& txt)
{
	/* In SFML, objects have an origin that act as the center of all transformations, such as
	 * rotation and position. The default value is the top left corner of said object
	 * (essetentially 0,0 in its local coordinate space). I find centering the origin
	 * makes transformations much easier thus this function.
	 */

	sf::FloatRect bounds = txt.getLocalBounds();

	txt.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
}

void SplashScreen::setSpriteOriginToCenter(sf::Sprite& spr)
{
	/* In SFML, objects have an origin that act as the center of all transformations, such as
	 * rotation and position. The default value is the top left corner of said object
	 * (essetentially 0,0 in its local coordinate space). I find centering the origin
	 * makes transformations much easier thus this function.
	 */

	sf::FloatRect bounds = spr.getLocalBounds();

	spr.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
}
