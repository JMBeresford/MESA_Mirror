#include <SFML/Graphics.hpp>
#include <fstream>
#include <experimental/filesystem>
#include "club.h"
#include "member.h"
#include "nlohmann/json.hpp"
using nlohmann::json;

namespace fs = std::experimental::filesystem;

Club::Club()
{
    this->name = "";
    this->description = "";
    this->president = "";
    this->email = "";
}
Club::Club(std::string& name,std::string& desc,std::string& pres,std::string& email, std::vector<Member> members)
{
    this->name = name;
    this->description = desc;
    this->president = pres;
    this->email = email;
    this->memberList = members;
}

std::string Club::getName()
{
    return this->name;
}

std::string Club::getDescription()
{
    return this->description;
}

std::string Club::getPresident()
{
    return this->president;
}

std::string Club::getEmail()
{
    return this->email;
}

std::string Club::fmtDescription(sf::RenderWindow& window, std::string s)
{
    int charLimit = (window.getSize().x) / 25;
    int lines = s.size()/charLimit;
    std::string temp = "";

    if (s.size() < charLimit)
        return s;
    else
    {
        bool newLine = 0;
        for (size_t i = 0; i < s.size(); i++)
        {
            if (i % charLimit == 0 && i != 0)
                newLine = 1;

            if (newLine == 1 && s[i-1] == ' ')
            {
                temp += '\n';
                temp += s[i];
                newLine = 0;
            }
            else
                temp += s[i];
        }
        return temp;
    }
}

void Club::addMember(Member m)
{
    std::fstream _file;
    std::string fpath = "clubs/" + this->getName() + ".json";

    this->memberList.emplace_back(m);

    json j = json::object(), j_member;

    j_member["fname"] = m.getFirstName();
    j_member["lname"] = m.getLastName();
    j_member["email"] = m.getEmail();
    j_member["phone"] = m.getPhone();

    _file.open(fpath, std::ios_base::in);

    _file >> j;
    _file.close();

    j["members"][m.getFmtName()] = j_member;

    _file.open(fpath, std::ios_base::out);

    _file << j.dump(1,'\t');
}

void to_json(json& j, const Club& c)
{
        j = json{{"name", c.name}, {"description", c.description},
            {"president", c.president}, {"email", c.email}};
}

void from_json(const json& j, Club& c)
{
        j.at("name").get_to(c.name);
        j.at("description").get_to(c.description);
        j.at("president").get_to(c.president);
        j.at("email").get_to(c.email);
}
