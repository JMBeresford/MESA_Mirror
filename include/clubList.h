#include <SFML/Graphics.hpp>
#include <vector>
#include <experimental/filesystem>
#include "club.h"

class ClubList : public sf::RenderTexture
{
public:
    ClubList(sf::RenderWindow& window);
    unsigned size();
    Club getClub(unsigned);

private:
    std::vector<Club> clubs;
    std::experimental::filesystem::path cwd;
};