#include <SFML/Graphics.hpp>
#include <ctime>
#include "splashScreen.h"

SplashScreen::SplashScreen(sf::RenderWindow& w)
{
    /*
    This class is an object that contains the Sprite and Text objects that are displayed
    on the splash screen (first screen to be displayed). Most of the setup here should
    be self explanatory. Be aware that this class, like the Screen class and all other
    classes that represent a 'menu' or 'screen' in the program, inherits from 
    sf::RenderTexture.
    */

    sf::Vector2f screenSize = sf::Vector2f(w.getSize());
    this->create(screenSize.x, screenSize.y);
    this->time = std::time(NULL);

    this->fnt.loadFromFile("assets/bladeRunner.ttf");
    this->enterText.setFont(this->fnt);
    this->mesaText.setFont(this->fnt);
    this->timeText.setFont(this->fnt);
    
    this->enterText.setString("Enter");
    this->mesaText.setString("CODCS");

    this->enterText.setCharacterSize(55); // Sets font size
    this->mesaText.setCharacterSize(55);
    this->timeText.setCharacterSize(35);

    this->ringTex.loadFromFile("assets/ring.png");
    this->shadowTex.loadFromFile("assets/ringShadow.png");

    this->ring.setTexture(ringTex);
    // We use a seperate shadow texture to create a 3d-like effect
    this->shadow.setTexture(shadowTex);

    setTextOriginToCenter(this->mesaText);
    setTextOriginToCenter(this->enterText);

    setSpriteOriginToCenter(this->ring);
    setSpriteOriginToCenter(this->shadow);

    this->ring.setPosition(sf::Vector2f(screenSize.x / 2.0f, screenSize.y / 2.0f));
    this->shadow.setPosition(sf::Vector2f(screenSize.x / 2.0f, screenSize.y / 2.0f));

    // Holds the dimensions of both text objects for use in setting position
    // largely to create padding between the two text objects
    sf::FloatRect textSize = this->enterText.getLocalBounds();

    this->enterText.setPosition(sf::Vector2f(screenSize.x / 2.0f,
								screenSize.y / 2.0f - (textSize.height / 2 + 5)));

    this->mesaText.setPosition( sf::Vector2f(screenSize.x / 2.0f,
							    screenSize.y / 2.0f + (textSize.height / 2 + 5)));
}

void SplashScreen::drawAll()
{
    this->draw(this->ring);
    this->draw(this->shadow);
    this->draw(this->enterText);
    this->draw(this->mesaText);
    this->draw(this->timeText);
}

void SplashScreen::rotateRing(int i)
{
    this->ring.rotate(i);
}

sf::FloatRect SplashScreen::getRingPos()
{
    return this->ring.getGlobalBounds();
}

std::string SplashScreen::doTime(sf::Vector2f& screenSize)
{
    // Read the ctime docs at cppreference website to better understand these functions
    char timeStr[9];
    struct tm* timeinfo;
    this->time = std::time(NULL); // Sets the time object to current time (rawtime)
    timeinfo = std::localtime(&this->time); // Sets to local time

    std::strftime(timeStr,9,"%I:%M:%S",timeinfo); // Creates string of human readable local time
    this->timeText.setString(timeStr);

    setTextOriginToCenter(this->timeText); // Needs to be done every time the string changes
    this->timeText.setPosition( sf::Vector2f(screenSize.x / 2.0f,
                                screenSize.y / 20.0f));
    return timeStr; // returns it as string
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
