#include <fstream>
#include <string>
#include <iostream>
#include <experimental/filesystem>
#include "nlohmann/json.hpp"
#include "clubList.h"

ClubList::ClubList(sf::RenderWindow& window)
{
    sf::Vector2f screenSize = sf::Vector2f(window.getSize());
    this->margin = sf::Vector2f(screenSize.x / 18, screenSize.y / 18);
    sf::Vector2f usableScreen(screenSize.x - 2 * margin.x, screenSize.y - 2 * margin.y);
    this->fnt.loadFromFile("assets/font.ttf");
    this->create(screenSize.x, screenSize.y);
    std::string tempDir = std::experimental::filesystem::current_path();
    tempDir += "/clubs";

    this->cwd = std::experimental::filesystem::path(tempDir);\

    for (auto file : std::experimental::filesystem::directory_iterator(this->cwd))
    {
        std::string filePath = file.path().filename();
        filePath = "clubs/" + filePath;
        std::ifstream inFile(filePath);
        std::vector<Member> members;

        json j;

        inFile >> j;

        inFile.close();

        std::string name = j["name"],
                    description = j["description"],
                    president = j["president"],
                    email = j["email"];

        for (auto i : j["members"])
        {
            std::string fname = i["fname"],
                        lname = i["lname"],
                        email = i["email"],
                        phone = i["phone"];

            members.emplace_back(Member(fname, lname, email, phone));
        }

        Club c(name, description, president, email, members);

        this->clubs.emplace_back(c);
    }

    
    this->grid.x = 2;
    if (this->clubs.size() % 2 == 0)
        this->grid.y = this->clubs.size() / 2;
    else
        this->grid.y = (this->clubs.size() + 1) / 2;

    this->cellSize.x = usableScreen.x/this->grid.x;
    this->cellSize.y = usableScreen.y/this->grid.y;

    for (size_t i = 0; i < this->grid.y; i++)
    {
        sf::FloatRect temp1(
            sf::Vector2f(margin.x,margin.y + (usableScreen.y/this->grid.y) * i),
            cellSize);

        sf::FloatRect temp2(
            sf::Vector2f(margin.x + usableScreen.x/2,margin.y + (usableScreen.y/this->grid.y) * i),
            cellSize);

        

        this->cells.push_back(temp1);
        this->cells.push_back(temp2);
    }

    for (size_t i = 0; i < this->clubs.size(); i++)
    {
        sf::Text temp(this->clubs[i].getName(),fnt,30);
        temp.setStyle(sf::Text::Bold);
        this->setTextOriginToCenter(temp);
        temp.setPosition(sf::Vector2f(
            this->cells[i].left + this->cells[i].width/2,
            this->cells[i].top + this->cells[i].height/2
        ));

        this->names.push_back(temp);
    }
}

bool ClubList::hovering(sf::Vector2f mousePos)
{
    auto texts = this->getTexts();
    for (auto i : texts)
    {
        if (i.getGlobalBounds().contains(mousePos))
            return true;
    }
    
    return false;
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