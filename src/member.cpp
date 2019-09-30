#include "member.h"

Member::Member( std::string fname, std::string lname, std::string email,
                std::string phone)
{
    this->fname = fname;
    this->lname = lname;
    this->email = email;
    this->phone = phone;
}