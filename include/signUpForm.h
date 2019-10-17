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
    std::vector<sf::FloatRect> clickables;
    sf::RectangleShape submit;

    void setTextOriginToCenter(sf::Text&);
    void setSpriteOriginToCenter(sf::RectangleShape&);
    void activateText(unsigned);
    void deactivate();
    void submitMember(Member);
    bool hovering(sf::Vector2f);

    struct textBox : public sf::RectangleShape
    {
        textBox()  {this->active = false;
                    this->setFillColor(sf::Color::White);}
        bool active;
        std::string str;
    };
    std::vector<textBox> textBoxes;

private:
    Club _club;
    sf::Font fnt;
    std::string fName, lName, email, phone;
    sf::Text name, description, firstName, lastName, _email, _phone, submitText;
    std::vector<sf::RectangleShape> hDivs;
};
#endif