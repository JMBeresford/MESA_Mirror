#include "signUpForm.h"
#include "club.h"

SignUpForm::SignUpForm(sf::RenderWindow& window, Club& _club)
{
    // TODO: redo this entire mess
    this->fnt.loadFromFile("assets/font.ttf");
    
    sf::Vector2f    screenSize = sf::Vector2f(window.getSize()),
                    margin = sf::Vector2f(screenSize.x/10,screenSize.y/10);

    this->create(screenSize.x, screenSize.y);

    this->_club = _club;

    std::string fmtdDesc = _club.fmtDescription(window,_club.getDescription());

    this->name = (sf::Text(_club.getName(), this->fnt, 45));

    this->description = (sf::Text(fmtdDesc, this->fnt, 25));

    this->firstName = (sf::Text("First Name:",this->fnt,25));

    this->lastName = (sf::Text("Last Name:",this->fnt,25));

    this->_email = (sf::Text("    Email:",this->fnt,25));

    this->_phone = (sf::Text("    Phone:",this->fnt,25));

    for (size_t i = 0; i < 4; i++)
    {
        textBox temp;
        this->setSpriteOriginToCenter(temp);
        temp.setFillColor(sf::Color(150,150,150,255));
        temp.setSize(sf::Vector2f(  this->_email.getLocalBounds().width*4,
                                    this->_email.getLocalBounds().height*1.5));

        temp.setPosition(sf::Vector2f(  screenSize.x/5 + _email.getLocalBounds().width,
                                        screenSize.y/2 + (this->firstName.getLocalBounds().height * 3 * i)));
        this->textBoxes.emplace_back(temp);
    }

    this->setTextOriginToCenter(this->name);
    this->setTextOriginToCenter(this->description);
    this->setTextOriginToCenter(this->firstName);
    this->setTextOriginToCenter(this->lastName);
    this->setTextOriginToCenter(this->_email);
    this->setTextOriginToCenter(this->_phone);

    this->name.setFillColor(sf::Color::White);
    this->description.setFillColor(sf::Color::White);
    this->firstName.setFillColor(sf::Color::White);
    this->lastName.setFillColor(sf::Color::White);
    this->_email.setFillColor(sf::Color::White);
    this->_phone.setFillColor(sf::Color::White);

    this->name.setPosition(screenSize.x/2, margin.y);

    sf::FloatRect textSize = this->name.getLocalBounds();

    this->description.setPosition(screenSize.x/2, this->description.getLocalBounds().height/2
                                                + margin.y + textSize.height * 3);

    this->firstName.setPosition(screenSize.x/5, screenSize.y/2);

    textSize = this->firstName.getLocalBounds();

    this->lastName.setPosition(screenSize.x/5, screenSize.y/2 + textSize.height * 3);

    this->_email.setPosition(screenSize.x/5, screenSize.y/2 + textSize.height * 6);

    this->_phone.setPosition(screenSize.x/5, screenSize.y/2 + textSize.height * 9);

    this->submit.setSize(sf::Vector2f(screenSize.x/5,screenSize.y/10));
    this->submit.setFillColor(sf::Color::White);
    this->setSpriteOriginToCenter(this->submit);
    this->submit.setPosition(screenSize.x/2, 8*screenSize.y/10);

    this->submitText.setFont(this->fnt);
    this->submitText.setString("SUBMIT");
    this->submitText.setFillColor(sf::Color::Black);
    this->setTextOriginToCenter(this->submitText);
    this->submitText.setPosition(screenSize.x/2, 8*screenSize.y/10);

    for (auto i : this->textBoxes)
        this->clickables.push_back(i.getGlobalBounds());

    this->clickables.push_back(this->submit.getGlobalBounds());
}

void SignUpForm::drawElements()
{
    this->draw(this->name);
    this->draw(this->description);
    this->draw(this->firstName);
    this->draw(this->lastName);
    this->draw(this->_email);
    this->draw(this->_phone);
    this->draw(this->submit);
    this->draw(this->submitText);
    
    for (auto i : this->textBoxes)
    {
        this->draw(i);
    }
}

void SignUpForm::activateText(unsigned i)
{
    for (size_t j = 0; j < this->textBoxes.size(); j++)
    {
        if (j == i)
            {
            this->textBoxes[j].setFillColor(sf::Color::White);
            this->textBoxes[j].active = true;
            }
        else
            this->textBoxes[j].setFillColor(sf::Color(150,150,150,255));
    }
}

void SignUpForm::deactivate()
{
    for (auto i : this->textBoxes)
    {
        i.active = false;
        i.setFillColor(sf::Color(150,150,150,255));
    }
}

bool SignUpForm::hovering(sf::Vector2f mousePos)
{
    for (auto i : this->clickables)
    {
        if (i.contains(mousePos))
            return true;
    }
    
    return false;
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

void SignUpForm::setSpriteOriginToCenter(sf::RectangleShape& spr)
{
	/* In SFML, objects have an origin that act as the center of all transformations, such as
	 * rotation and position. The default value is the top left corner of said object
	 * (essetentially 0,0 in its local coordinate space). I find centering the origin
	 * makes transformations much easier thus this function.
	 */

	sf::FloatRect bounds = spr.getLocalBounds();

	spr.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
}
