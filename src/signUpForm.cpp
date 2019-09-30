#include "signUpForm.h"
#include "club.h"

SignUpForm::SignUpForm(sf::RenderWindow& window, Club& _club)
{
    sf::Font fnt;
    fnt.loadFromFile("assets/bladeRunner.ttf");
    
    sf::Vector2f    screenSize = sf::Vector2f(window.getSize()),
                    margin = sf::Vector2f(screenSize.x/15,screenSize.y/15);

    this->_club = _club;

    this->texts.push_back(sf::Text(this->_club.name, fnt, 45));

    this->texts.push_back(sf::Text(this->_club.description, fnt, 30));

    this->texts.push_back(sf::Text("First Name:",fnt,25));

    this->texts.push_back(sf::Text("Last Name:",fnt,25));

    this->texts.push_back(sf::Text("    Email:",fnt,25));

    this->texts.push_back(sf::Text("    Phone:",fnt,25));


    for (auto i : this->texts)
        this->setTextOriginToCenter(i);

    this->texts[0].setPosition(screenSize.x/2, margin.y);

    sf::FloatRect textSize = this->texts[0].getLocalBounds();

    this->texts[1].setPosition(screenSize.x/2, margin.y + textSize.height * 1.5);

    this->texts[2].setPosition(screenSize.x/4, screenSize.y/2);

    textSize = this->texts[2].getLocalBounds();

    this->texts[3].setPosition(screenSize.x/4, screenSize.y/2 + textSize.height * 1.5);

    this->texts[4].setPosition(screenSize.x/4, screenSize.y + textSize.height * 3);
}

void SignUpForm::drawElements()
{
    for (auto i : this->texts)
        this->draw(i);

    for (auto i : this->textBoxes)
        this->draw(i);
}

void SignUpForm::setTextOriginToCenter(sf::Text& txt)
{
	/* In SFML, objects have an origin that act as the center of all transformations, such as
	 * rotation and position. The default value is the top left corner of said object
	 * (essetentially 0,0 in its local coordinate space). I find centering the origin
	 * makes transformations much easier thus this function.
	 */

	sf::FloatRect bounds = txt.getLocalBounds();

	txt.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
}

void SignUpForm::setSpriteOriginToCenter(sf::Sprite& spr)
{
	/* In SFML, objects have an origin that act as the center of all transformations, such as
	 * rotation and position. The default value is the top left corner of said object
	 * (essetentially 0,0 in its local coordinate space). I find centering the origin
	 * makes transformations much easier thus this function.
	 */

	sf::FloatRect bounds = spr.getLocalBounds();

	spr.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
}
