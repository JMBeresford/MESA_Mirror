#ifndef MEMBER_H
#define MEMBER_H
#include <string>
#include "nlohmann/json.hpp"

class Member
{
public:
    Member(std::string,std::string,std::string,std::string);

    std::string getName() {return this->fname + this->lname;}
    std::string getEmail() {return this->email;}
    std::string getPhone() {return this->phone;}
    std::string dump();

private:
    std::string fname, lname, email, phone;
};
#endif