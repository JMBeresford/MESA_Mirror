#ifndef CLUB_H
#define CLUB_H
#include <string>
#include <vector>
#include "member.h"
#include <SFML/Graphics.hpp>
#include "nlohmann/json.hpp"
using nlohmann::json;

struct Club
{
    Club();
    Club(   std::string& name,
            std::string& description,
            std::string& president,
            std::string& email,
            std::vector<Member>);

    std::string getName();
    std::string getDescription();
    std::string getPresident();
    std::string getEmail();
    std::string fmtDescription(sf::RenderWindow&,std::string);
    void addMember(Member);
    void to_json(json&, const Club&);
    void from_json(const json&, Club&);

    std::string name, description, president, email;
    std::vector<Member> memberList;
};
#endif