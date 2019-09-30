#ifndef SIGNUPFORM_H
#define SIGNUPFORM_H
#include <SFML/Graphics.hpp>
#include "club.h"

class SignUpForm : public sf::RenderTexture
{
public:
    SignUpForm(sf::RenderWindow&,Club);
    void drawElements();

private:
    Club _club;
};
#endif