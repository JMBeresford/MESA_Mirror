#include <string>
#include "nlohmann/json.hpp"
using nlohmann::json;

struct Club
{
    Club();
    Club(   std::string& name,
            std::string& description,
            std::string& president,
            std::string& email);

    std::string getName();
    std::string getDescription();
    std::string getPresident();
    std::string getEmail();
    void to_json(json&, const Club&);
    void from_json(const json&, Club&);

    std::string name, description, president, email;
};