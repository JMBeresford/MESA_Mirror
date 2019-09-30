#ifndef CLUBLIST_H
#define CLUBLIST_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <experimental/filesystem>
#include "club.h"

class ClubList : public sf::RenderTexture
{
public:
    ClubList(sf::RenderWindow& window);
    unsigned size();
    void setTextOriginToCenter(sf::Text&);
    void setSpriteOriginToCenter(sf::Sprite&);
    Club getClub(unsigned);
    void drawClubs();

private:
    sf::Font fnt;
    sf::Vector2f grid, cellSize, margin;
    std::vector<Club> clubs;
    std::vector<sf::Text> names;
    std::experimental::filesystem::path cwd;
};
#endif