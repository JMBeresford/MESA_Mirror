#include <SFML/Graphics.hpp>
#include <vector>
#include "club.cpp"
namespace fs = std::experimental::filesystem;

class ClubList : public sf::RenderTexture
{
public:
    ClubList(sf::RenderWindow& window);
    unsigned size();
    Club getClub(unsigned);

private:
    std::vector<Club> clubs;
    fs::path cwd;
};