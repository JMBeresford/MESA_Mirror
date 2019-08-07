#include <SFML/Graphics.hpp>
#include <vector>
#include "../src/animatedSprite.hpp"

class Screen : public sf::RenderTexture
{
public:
    Screen(sf::RenderWindow&);
    
    void animate();
    void drawCorners();
    void setSpriteOriginToCenter(AnimatedSprite&);

private:
    sf::Texture corner;
    std::vector<AnimatedSprite> cornerSprites;
    sf::Vector2f screenSize, margin;
};