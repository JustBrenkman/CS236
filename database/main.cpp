//
// Created by bbrenk on 10/24/18.
//

#include <iostream>
#include "Relation.h"

int main(int argc, char **argv) {

    auto relation = new Relation();
    relation->addColumns("A", "B", "C", "D");
    relation->insertRows({{"Hello", "Hello", "Hello", "Hello"},
                          {"Hello", "list",  "That",  "Super long string just for fun"}});
    relation->setName("R");

    auto second = relation->select(std::make_pair("A", "Hello"), std::make_pair("B", "list"));
    second->setName("Q");
    auto third = relation->project("A", "D");
    auto fourth = relation->rename(std::make_pair("A", "1"), std::make_pair("B", "2"), std::make_pair("C", "3"),
                                   std::make_pair("D", "4"));

    std::cout << "DATABASE: RELATION" << std::endl << *relation << std::endl;
    std::cout << "SELECT:" << std::endl << *second << std::endl;
    std::cout << "PROJECT:" << std::endl << *third << std::endl;
    std::cout << "RENAME:" << std::endl << *fourth << std::endl;

    delete relation;
    delete second;
    delete third;
    delete fourth;

    return 0;
}
