#ifndef SCREEN_H
#define SCREEN_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "animatedSprite.h"

class Screen : public sf::RenderTexture
{
public:
    Screen(sf::RenderWindow&); // ctor
    
    void animate(); // Will be used to call the animate functions of the AnimatedSprites
    void drawCorners(); // Used to draw the AnimatedSprites
    void setSpriteOriginToCenter(AnimatedSprite&); // Check definition in src folder

private:
    sf::Texture corner;
    std::vector<AnimatedSprite> cornerSprites;
    sf::Vector2f screenSize, margin;
};
#endif