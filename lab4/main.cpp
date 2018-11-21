//
// Created by justb on 11/18/2018.
//

#include "Relation.h"
#include <iostream>

int main(int argc, char** argv) {
    auto r = new Relation();
    r->setName("R");
    r->addColumns("B", "A", "C");
    r->insertRows({{"B", "A", "C"}, {"B", "A", "C"}, {"B", "A", "C"}});
    std::cout << *r << std::endl;

    auto t = new Relation();
    t->setName("T");
    t->addColumns("C", "D");
    t->insertRows({{"B", "C", ""}, {"A", "B"}, {"C", "D"}});
    std::cout << *t << std::endl;

    auto result = r->join(t);
    std::cout << *result << std::endl;

    return 0;
}