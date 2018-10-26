//
// Created by bbrenk on 10/24/18.
//

#include <iostream>
#include "Relation.h"

int main(int argc, char **argv) {
//    auto relation = new Relation();
//    relation->addColumns("A", "B", "C", "D");
//    relation->insertRows({{"Hello", "Hello", "Hello", "Hello"},
//                          {"Hello", "list",  "That",  "Super long string just for fun"}});
//    relation->setName("R");
//
//    auto second = relation->select(std::make_pair("A", "Hello"), std::make_pair("B", "C"));
//    second->setName("Q");
//    auto third = relation->project("A", "D");
//    auto fourth = relation->rename(std::make_pair("A", "1"), std::make_pair("B", "2"), std::make_pair("C", "3"), std::make_pair("D", "4"));
//
//    std::cout << "DATABASE: RELATION" << std::endl << *relation << std::endl;
//    std::cout << "SELECT:" << std::endl << *second << std::endl;
//    std::cout << "PROJECT:" << std::endl << *third << std::endl;
//    std::cout << "RENAME:" << std::endl << *fourth << std::endl;
//
//    delete relation;
//    delete second;
//    delete third;
//    delete fourth;

    // Test Case 1, 2, 3, 4
    auto Q = new Relation();
    Q->setName("Q");
    Q->addColumns("A", "B", "C");
    Q->insertRows({{"Bret",     "Mathew", "Johnson"},
                   {"Benjamin", "Geurt",  "Brenkman"},
                   {"Kayla",    "?",      "Cooper"},
                   {"Ben",      "Ben",    "Ben"},
                   {"Ben",      "Geurt",  "Brenkman"},
                   {"Bret",     "Bret",   "Cooper"},
                   {"Kayla",    "Cooper", "Cooper"}});

    std::cout << *Q << std::endl;

    // Select test: SELECT * WHERE A = Ben
    auto R = Q->select(std::make_pair("A", "Ben"), std::make_pair("C", "Brenkman"));
    R->setName("R");
    std::cout << *R << std::endl;

    // Testing same column select: SELECT * WHERE B=C
    auto M = Q->select(std::make_pair("B", "C"));
    M->setName("M");
    std::cout << *M << std::endl;

    // Testing both same column and column value select
    // SELECT * WHERE A = Kayla AND B=C
    auto N = Q->select(std::make_pair("A", "Kayla"), std::make_pair("B", "C"));
    N->setName("N");
    std::cout << *N << std::endl;

    // Rename Test: RENAME A='First Name', B='Middle Name', C='Last Name'
    auto L = R->rename(std::make_pair("A", "First Name"), std::make_pair("B", "Middle Name"),
                       std::make_pair("C", "Last Name"));
    L->setName("L");
    std::cout << *L << std::endl;

    // Projection test PROJECT 'First Name', 'Last Name'
    auto P = L->project("First Name", "Last Name");
    P->setName("P");
    std::cout << *P << std::endl;

    delete Q;
    delete R;
    delete L;
    delete M;
    delete N;
    delete P;

    return 0;
}
