#include <SFML/Graphics.hpp>

class Screen : public sf::RenderTexture
{
public:
    Screen(sf::RenderWindow&);
    void animate();

private:
    sf::Texture corner;
    sf::Sprite cornerSprites[4];
    sf::Font fnt;
    sf::Vector2f screenSize, margin;

};