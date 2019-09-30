#include <fstream>
#include <string>
#include <iostream>
#include <experimental/filesystem>
#include "nlohmann/json.hpp"
#include "clubList.h"

ClubList::ClubList(sf::RenderWindow& window)
{
    sf::Vector2f screenSize = sf::Vector2f(window.getSize());
    this->margin = sf::Vector2f(screenSize.x / 15, screenSize.y / 15);
    this->fnt.loadFromFile("assets/bladeRunner.ttf");
    this->create(screenSize.x, screenSize.y);
    std::string tempDir = std::experimental::filesystem::current_path();
    tempDir += "/clubs";

    this->cwd = std::experimental::filesystem::path(tempDir);\

    for (auto file : std::experimental::filesystem::directory_iterator(this->cwd))
    {
        std::string filePath = file.path().filename();
        filePath = "clubs/" + filePath;
        std::ifstream inFile(filePath);

        json j;

        inFile >> j;

        inFile.close();

        std::string name = j["name"],
                    description = j["description"],
                    president = j["president"],
                    email = j["email"];

        Club c(name, description, president, email);

        this->clubs.emplace_back(c);
    }

    
    this->grid.x = 2;
    this->grid.y = this->clubs.size() / 2 + 1;
    this->cellSize.x = (screenSize.x - this->margin.x * 2) / this->grid.x;
    this->cellSize.y = (screenSize.y - this->margin.y * 2) / this->grid.y;

    for (size_t i = 0; i < this->clubs.size(); i++)
    {
        sf::Text temp(this->clubs[i].getName(),fnt,30);
        this->setTextOriginToCenter(temp);
        sf::FloatRect textSize(temp.getLocalBounds());
        temp.setPosition(sf::Vector2f(  this->margin.x/this->grid.x + screenSize.x/this->grid.x * (i%int(grid.x) + 1),
                                        this->margin.y/this->grid.y + screenSize.y/this->grid.y * (i / grid.x)));

        this->names.emplace_back(temp);
    }

    // The following is a lazy workaround for positioning the text
    // TODO: Fix this to be responsive to size of names vector
    this->names[0].setPosition(sf::Vector2f(
        screenSize.x/4 + this->margin.x, screenSize.y/2
    ));

    this->names[1].setPosition(sf::Vector2f(
        3*screenSize.x/4 - this->margin.x, screenSize.y/2
    ));
}

void ClubList::setTextOriginToCenter(sf::Text& txt)
{
	/* In SFML, objects have an origin that act as the center of all transformations, such as
	 * rotation and position. The default value is the top left corner of said object
	 * (essetentially 0,0 in its local coordinate space). I find centering the origin
	 * makes transformations much easier thus this function.
	 */

	sf::FloatRect bounds = txt.getLocalBounds();

	txt.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
}

void ClubList::setSpriteOriginToCenter(sf::Sprite& spr)
{
	/* In SFML, objects have an origin that act as the center of all transformations, such as
	 * rotation and position. The default value is the top left corner of said object
	 * (essetentially 0,0 in its local coordinate space). I find centering the origin
	 * makes transformations much easier thus this function.
	 */

	sf::FloatRect bounds = spr.getLocalBounds();

	spr.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
}

Club& ClubList::getClub(unsigned i)
{
    return this->clubs[i];
}

void ClubList::drawClubs()
{
    for (auto i : this->names)
        this->draw(i);
}

std::vector<sf::Text> ClubList::getTexts()
{
    return this->names;
}