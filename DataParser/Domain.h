//
// Created by bbrenk on 10/15/18.
//

#ifndef LAB2_DOMAIN_H
#define LAB2_DOMAIN_H


#include "DLString.h"
#include "Fact.h"

class Domain {
private:
    std::vector<std::string> domain;
public:
    Domain();

    void addStringToDomain(std::string string);

    std::string toString();
};


#endif //LAB2_DOMAIN_H
