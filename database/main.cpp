//
// Created by bbrenk on 10/24/18.
//

#include <iostream>
#include "Relation.h"

int main(int argc, char **argv) {
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

    auto SK = new Relation();
    SK->setName("SK");
    SK->addColumns("A", "B");
    SK->insertRows({{"a", "c"},
                    {"b", "c"},
                    {"b", "b"},
                    {"b", "c", ""}});

    std::cout << *SK << std::endl;

    // Query Test 1 SK(A, 'c');
    auto project1 = SK->select(std::make_pair("B", "c"));
    auto result = project1->project("A");
    std::cout << *result << std::endl;

    delete project1;
    delete result;

    // Query Test 2 SK('b', 'c');
    result = SK->select(std::make_pair("A", "b"), std::make_pair("B", "c"));
    result->setName("Result");
    std::cout << *result << std::endl;
    delete result;

    auto table2 = SK->select(std::make_pair("A", "B"));
    table2->setName("S");
    auto table3 = table2->rename(std::make_pair("A", "X"));
    table3->setName("K");
    result = table3->project("X");
    result->setName("Result");
    std::cout << *result << std::endl;

    delete table2;
    delete table3;

    result = SK->project("A", "B");
    result->setName("Result");
    std::cout << *result << std::endl;

    delete SK;
    delete result;

    return 0;
}
