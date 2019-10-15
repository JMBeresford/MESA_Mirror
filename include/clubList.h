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
    unsigned size() {return this->clubs.size();}
    void setTextOriginToCenter(sf::Text&);
    void setSpriteOriginToCenter(sf::Sprite&);
    Club& getClub(unsigned i);
    void drawClubs();
    bool hovering(sf::Vector2f);

    std::vector<sf::Text> getTexts();
    std::vector<sf::FloatRect> cells;

private:
    sf::Font fnt;
    sf::Vector2f grid, cellSize, margin;
    std::vector<Club> clubs;
    std::vector<sf::Text> names;
    std::experimental::filesystem::path cwd;
};
#endif