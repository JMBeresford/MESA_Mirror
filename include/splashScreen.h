#include <SFML/Graphics.hpp>

class SplashScreen : public sf::RenderTexture
{
public:
    SplashScreen(sf::RenderWindow&); // ctor

    void rotateRing(int);
    void setTextOriginToCenter(sf::Text&);
    void setSpriteOriginToCenter(sf::Sprite&);
    sf::FloatRect getRingPos();
    void drawAll(); // Draws all objects to the RenderTexture
    std::string doTime(sf::Vector2f&); // Sets clock and positions it

private:
    sf::Font fnt;
    std::time_t time;
    sf::Texture ringTex, shadowTex;
    sf::Sprite ring, shadow;
    sf::Text mesaText, enterText, timeText;
};