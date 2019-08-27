#include <fstream>
#include <string>
#include <iostream>
#include <experimental/filesystem>
#include "clubList.h"

namespace fs = std::experimental::filesystem;

ClubList::ClubList(sf::RenderWindow& window)
{
    sf::Vector2f screenSize = sf::Vector2f(window.getSize());
    this->create(screenSize.x, screenSize.y);
    std::string tempDir = fs::current_path();
    tempDir += "/clubs";

    this->cwd = fs::path(tempDir);\

    for (auto file : fs::directory_iterator(this->cwd))
    {
        std::string filePath = file.path().filename();
        filePath = "clubs/" + filePath;
        std::ifstream inFile(filePath);

        json j;

        inFile >> j;

        inFile.close();

        auto c = j.get<Club>();

        this->clubs.push_back(c);
    }

    for (auto c : this->clubs)
    {
        std::cout << c.getName() << " " << c.getEmail();
    }
}