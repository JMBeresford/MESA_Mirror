#include <SFML/Graphics.hpp>
#include "../include/screen.h"

Screen::Screen(sf::RenderWindow& w)
{
    this->fnt.loadFromFile("../assets/bladeRunner.ttf");
    this->screenSize =  sf::Vector2f(w.getSize());
    this->margin = sf::Vector2f(this->screenSize.x * 1/15, this->screenSize.y * 1/15);
    this->corner.loadFromFile("../assets/corner.png");

    this->create(this->screenSize.x, this->screenSize.y);

    for(size_t i = 0; i < sizeof(this->cornerSprites)/sizeof(this->cornerSprites[0]); i++)
        this->cornerSprites[i].setTexture(this->corner);

    

}

void Screen::animate()
{

}