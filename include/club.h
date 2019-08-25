#include <string>

class Club
{
public:
    Club(   std::string& name,
            std::string& description,
            std::string& president,
            std::string& email);

    std::string getName();
    std::string getDescription();
    std::string getPresident();
    std::string getEmail();

private:
    std::string name, description, president, email;
};