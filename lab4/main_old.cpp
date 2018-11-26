//
// Created by bbrenk on 10/24/18.
//

#include <iostream>
#include "Relation.h"

void runTestsQuery() {

}

int main(int argc, char **argv) {

    auto R = new Relation();
    R->setName("R");
    R->addColumns("A", "B");
    R->insertRows({{"1", "2", ""}, {"2", "2"}, {"2", "3"}});

    auto S = new Relation();
    S->setName("S");
    S->addColumns("A", "B");
    S->insertRows({{"2", "2", ""}, {"2", "3"}, {"4", "2"}, {"5", "2"}});

    auto result = R->Union(S);
    std::cout << *result << std::endl;

    delete R;
    delete S;
    delete result;

    R = new Relation();
    R->setName("R");
    R->addColumns("A", "B");
    R->insertRows({{"1", "2", ""}, {"2", "2"}, {"2", "3"}});

    S = new Relation();
    S->setName("S");
    S->addColumns("B", "C");
    S->insertRows({{"1", "1", ""}, {"2", "2"}, {"3", "3"}});

    result = R->join(S);
    std::cout << *result << std::endl;

    delete R;
    delete S;
    delete result;

    R = new Relation();
    R->setName("R");
    R->addColumns("A", "B", "C");
    R->insertRows({{"1", "2", "3"}, {"2", "2", "4"}, {"2", "3", "5"}});

    S = new Relation();
    S->setName("S");
    S->addColumns("A", "B", "D");
    S->insertRows({{"1", "1", "1"}, {"2", "2", "2"}, {"2", "2", "1"}});

    result = R->join(S);
    std::cout << *result << std::endl;

    delete R;
    delete S;
    delete result;

    R = new Relation();
    R->setName("R");
    R->addColumns("A", "B");
    R->insertRows({{"1", "1", ""}, {"2", "3"}, {"4", "1"}});

    S = new Relation();
    S->setName("S");
    S->addColumns("C", "D");
    S->insertRows({{"1", "1"}, {"1", "5", ""}});

    result = R->join(S);
    std::cout << *result << std::endl;

    delete R;
    delete S;
    delete result;

    R = new Relation();
    R->setName("R");
    R->addColumns("A", "B");
    R->insertRows({{"1", "2", ""}, {"3", "4"}});

    S = new Relation();
    S->setName("S");
    S->addColumns("B", "C", "D");
    S->insertRows({{"2", "5", "1"}, {"2", "7", "2"}, {"3", "2", "3"}, {"4", "5", "4"}});

    result = R->join(S);
    std::cout << *result << std::endl;

    delete R;
    delete S;
    delete result;

    return 0;
}
