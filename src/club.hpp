#include "../include/club.h"

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
