#include <fstream>
#include <string>
#include <iostream>
#include <experimental/filesystem>
#include "nlohmann/json.hpp"
#include "clubList.h"

ClubList::ClubList(sf::RenderWindow& window)
{
    sf::Vector2f screenSize = sf::Vector2f(window.getSize());
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

        this->clubs.push_back(c);
    }

    for (auto c : this->clubs)
    {
        std::cout << c.getName() << " " << c.getEmail() << std::endl;
    }
}