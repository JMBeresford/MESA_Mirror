#include <SFML/Graphics.hpp>

class SplashScreen : public sf::RenderTexture
{
public:
    SplashScreen(sf::RenderWindow&);

    void rotateRing(int);
    void setTextOriginToCenter(sf::Text&);
    void setSpriteOriginToCenter(sf::Sprite&);
    sf::FloatRect getRingPos();
    void drawRing();

private:
    sf::Font fnt;
    sf::Texture ringTex, shadowTex;
    sf::Sprite ring, shadow;
    sf::Text mesaText, enterText;
};