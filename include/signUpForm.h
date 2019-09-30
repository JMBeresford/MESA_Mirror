#ifndef SIGNUPFORM_H
#define SIGNUPFORM_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "club.h"

class SignUpForm : public sf::RenderTexture
{
public:
    SignUpForm(sf::RenderWindow&,Club&);
    void drawElements();

    void setTextOriginToCenter(sf::Text&);
    void setSpriteOriginToCenter(sf::Sprite&);

    struct textBox : public sf::RectangleShape
    {
        textBox()  {this->active = false;
                    this->setFillColor(sf::Color::White);}
        bool active;
        std::string str;
    };

private:
    Club _club;
    std::string fName, lName, email, phone;
    std::vector<sf::Text> texts;
    std::vector<sf::RectangleShape> hDivs;
    std::vector<textBox> textBoxes;
    std::vector<sf::FloatRect> clickables;
};
#endif