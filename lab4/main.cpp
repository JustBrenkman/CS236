//
// Created by justb on 11/18/2018.
//

#include "Relation.h"
#include <iostream>

int main(int argc, char** argv) {
    auto r = new Relation();
    r->setName("R");
    r->addColumns("A", "B", "C");
    r->insertRows({{"1", "2", "3"}, {"2", "2", "4"}, {"2", "3", "5"}});
    std::cout << *r << std::endl;

    auto t = new Relation();
    t->setName("T");
    t->addColumns("B", "D", "A");
    t->insertRows({{"1", "1", "1"}, {"2", "2", "2"}, {"2", "1", "2"}});
    std::cout << *t << std::endl;

    auto result = r->join(t);
    std::cout << *result << std::endl;

    r = new Relation();
    r->setName("R");
    r->addColumns("A", "B");
    r->insertRows({{"1", "2", ""}, {"2", "2"}, {"2", "3"}});
    std::cout << *r << std::endl;

    auto s = new Relation();
    s->setName("S");
    s->addColumns("A", "B");
    s->insertRows({{"2", "2", ""}, {"2", "3"}, {"4", "2"}, {"5", "5"}});
    std::cout << *s << std::endl;

    result = r->Union(s);
    result->setName("Result");
    std::cout << *result << std::endl;

    return 0;
}