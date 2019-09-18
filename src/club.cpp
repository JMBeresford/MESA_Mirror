#include "club.h"
#include "nlohmann/json.hpp"
using nlohmann::json;

Club::Club()
{
    this->name = "";
    this->description = "";
    this->president = "";
    this->email = "";
}
Club::Club(std::string& name,std::string& desc,std::string& pres,std::string& email)
{
    this->name = name;
    this->description = desc;
    this->president = pres;
    this->email = email;
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
