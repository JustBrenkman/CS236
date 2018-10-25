//
// Created by bbrenk on 10/24/18.
//

#include <iostream>
#include "Relation.h"

int main(int argc, char **argv) {

    auto relation = new Relation();
    relation->addColumns("First", "Second", "Third", "Fourth");
    relation->insertRows({{"Hello", "Hello", "Hello", "Hello"},
                          {"Hello", "list",  "That"}});

    auto second = relation->select(std::make_pair("First", "Hello"), std::make_pair("Second", "list"));

    delete relation;
    delete second;

    return 0;
}
