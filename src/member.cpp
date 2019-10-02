#include "member.h"
#include <nlohmann/json.hpp>
using nlohmann::json;

Member::Member( std::string fname, std::string lname, std::string email,
                std::string phone)
{
    this->fname = fname;
    this->lname = lname;
    this->email = email;
    this->phone = phone;
}

std::string Member::dump()
{
    std::string str = this->fname + '&' + this->lname + '&' + this->email + '&' + this->phone + '*';
    return str;
}