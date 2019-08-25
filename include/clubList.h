#include <SFML/Graphics.hpp>
#include <vector>
#include "../src/club.hpp"

class ClubList : public sf::RenderTexture
{
public:
    ClubList(sf::RenderWindow& window);

private:
    std::vector<Club> clubs;
};