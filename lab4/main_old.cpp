//
// Created by bbrenk on 10/24/18.
//

#include <iostream>
#include "Relation.h"

int main(int argc, char **argv) {
    auto test1 = new Relation();
    auto test2 = new Relation();
    auto test3 = new Relation();
    auto test4 = new Relation();
    auto test5 = new Relation();
    auto test6 = new Relation();
    auto test7 = new Relation();
    auto test8 = new Relation();
    auto test9 = new Relation();
    auto test10 = new Relation();

    test1->addColumns("A", "B");
    test1->insertRows({{"1", "2", ""},
                       {"2", "2"},
                       {"2", "3"},
                       {"4", "2"},
                       {"5", "2"}});

    test2->addColumns("A", "B", "C");
    test2->insertRows({{"1", "2", "2"},
                       {"2", "2", "2"},
                       {"2", "3", "3"}});

    test3->addColumns("A", "B", "C", "D");
    test3->insertRows({{"2", "2", "4", "2"},
                       {"2", "2", "4", "1"}});

    test4->addColumns("A", "B", "C", "D");
    test4->insertRows({{"1", "1", "1", "1"},
                       {"1", "1", "1", "5"},
                       {"2", "3", "1", "1"},
                       {"2", "3", "1", "5"},
                       {"4", "1", "1", "1"},
                       {"4", "1", "1", "5"}});

    test5->addColumns("A", "B", "C", "D");
    test5->insertRows({{"1", "2", "5", "1"},
                       {"1", "2", "7", "2"},
                       {"3", "4", "5", "4"}});

    test6->addColumns("B", "A");
    test6->insertRows({"1", "1", ""});

    test7->addColumns("A", "B", "C");
    test7->insertRows({{"1",  "2",  "3"},
                       {"2",  "3",  "4"},
                       {"3",  "4",  "5"},
                       {"4",  "5",  "6"},
                       {"5",  "6",  "7"},
                       {"6",  "7",  "8"},
                       {"7",  "8",  "9"},
                       {"8",  "9",  "10"},
                       {"9",  "10", "11"},
                       {"10", "11", "12"},
                       {"11", "12", "13"},
                       {"12", "13", "14"}});

    test8->addColumns("A", "B");
    test8->insertRows({{"1", "2", ""},
                       {"2", "2"},
                       {"2", "3"},
                       {"4", "2"},
                       {"5", "5"}});

    test9->addColumns("A", "B", "C");
    test9->insertRows({{"1", "2", "3"},
                       {"2", "2", "5"},
                       {"2", "2", "6"},
                       {"2", "2", "8"},
                       {"2", "3", "8"},
                       {"2", "3", "9"}});

    test10->addColumns("A", "B", "C", "D");
    test10->insertRows({{"1", "2", "3", "4"},
                        {"2", "2", "2", "2"},
                        {"2", "3", "1", "4"},
                        {"2", "3", "2", "3"},
                        {"3", "2", "2", "3"}});


    // Union Test Cases

    // Test case 1: Same column names
    auto R = new Relation();
    R->setName("R");
    R->addColumns("A", "B");
    R->insertRows({{"1", "2", ""},
                   {"2", "2"},
                   {"2", "3"}});

    auto S = new Relation();
    S->setName("S");
    S->addColumns("A", "B");
    S->insertRows({{"2", "2", ""},
                   {"2", "3"},
                   {"4", "2"},
                   {"5", "2"}});

    auto result = R->Union(S);
    std::cout << "TEST 1: " << ((*result == *test1) ? "PASSED" : "FAILED") << std::endl;
    std::cout << *result << std::endl;

    delete R;
    delete S;
    delete result;

    // Test case 2: Only 1 same column
    R = new Relation();
    R->setName("R");
    R->addColumns("A", "B");
    R->insertRows({{"1", "2", ""},
                   {"2", "2"},
                   {"2", "3"}});

    S = new Relation();
    S->setName("S");
    S->addColumns("B", "C");
    S->insertRows({{"1", "1", ""},
                   {"2", "2"},
                   {"3", "3"}});

    result = R->join(S);
    std::cout << "TEST 2: " << ((*result == *test2) ? "PASSED" : "FAILED") << std::endl;
    std::cout << *result << std::endl;

    delete R;
    delete S;
    delete result;

    // Test case 3: two columns with same name
    R = new Relation();
    R->setName("R");
    R->addColumns("A", "B", "C");
    R->insertRows({{"1", "2", "3"},
                   {"2", "2", "4"},
                   {"2", "3", "5"}});

    S = new Relation();
    S->setName("S");
    S->addColumns("A", "B", "D");
    S->insertRows({{"1", "1", "1"},
                   {"2", "2", "2"},
                   {"2", "2", "1"}});

    result = R->join(S);
    std::cout << "TEST 3: " << ((*result == *test3) ? "PASSED" : "FAILED") << std::endl;
    std::cout << *result << std::endl;

    delete R;
    delete S;
    delete result;

    // Test case 4: No columns have the same, perform cross product
    R = new Relation();
    R->setName("R");
    R->addColumns("A", "B");
    R->insertRows({{"1", "1", ""},
                   {"2", "3"},
                   {"4", "1"}});

    S = new Relation();
    S->setName("S");
    S->addColumns("C", "D");
    S->insertRows({{"1", "1"},
                   {"1", "5", ""}});

    result = R->join(S);
    std::cout << "TEST 4: " << ((*result == *test4) ? "PASSED" : "FAILED") << std::endl;
    std::cout << *result << std::endl;

    delete R;
    delete S;
    delete result;

    // Test case 5: Second table has more columns than first, testing with one column that has same value
    R = new Relation();
    R->setName("R");
    R->addColumns("A", "B");
    R->insertRows({{"1", "2", ""},
                   {"3", "4"}});

    S = new Relation();
    S->setName("S");
    S->addColumns("B", "C", "D");
    S->insertRows({{"2", "5", "1"},
                   {"2", "7", "2"},
                   {"3", "2", "3"},
                   {"4", "5", "4"}});

    result = R->join(S);
    std::cout << "TEST 5: " << ((*result == *test5) ? "PASSED" : "FAILED") << std::endl;
    std::cout << *result << std::endl;

    delete R;
    delete S;
    delete result;

    // Test case 6: Column order doesnt match
    R = new Relation();
    R->setName("E");
    R->addColumns("B", "A");
    R->insertRows({{"1", "1", ""},
                   {"1", "2"},
                   {"2", "2"},
                   {"2", "3"},
                   {"3", "3"},
                   {"3", "4"},
                   {"4", "4"},
                   {"4", "1"}});

    S = new Relation();
    S->setName("S");
    S->addColumns("A", "B");
    S->insertRows({"1", "1", ""});

    result = R->join(S);
    std::cout << "TEST 6: " << ((*result == *test6) ? "PASSED" : "FAILED") << std::endl;
    std::cout << *result << std::endl;

    delete R;
    delete S;
    delete result;

    // Test case 7: Larger case, stress test on speed of join function
    R = new Relation();
    R->setName("E");
    R->addColumns("A", "B");
    R->insertRows({{"1",  "2", ""},
                   {"2",  "3"},
                   {"3",  "4"},
                   {"4",  "5"},
                   {"5",  "6"},
                   {"6",  "7"},
                   {"7",  "8"},
                   {"8",  "9"},
                   {"9",  "10"},
                   {"10", "11"},
                   {"11", "12"},
                   {"12", "13"},
                   {"13", "14"}});

    S = new Relation();
    S->setName("S");
    S->addColumns("B", "C");
    S->insertRows({{"1",  "2", ""},
                   {"2",  "3"},
                   {"3",  "4"},
                   {"4",  "5"},
                   {"5",  "6"},
                   {"6",  "7"},
                   {"7",  "8"},
                   {"8",  "9"},
                   {"9",  "10"},
                   {"10", "11"},
                   {"11", "12"},
                   {"12", "13"},
                   {"13", "14"}});

    result = R->join(S);
    std::cout << "TEST 7: " << ((*result == *test7) ? "PASSED" : "FAILED") << std::endl;
    std::cout << *result << std::endl;

    delete R;
    delete S;
    delete result;

    // Test case 8: Union test simple
    R = new Relation();
    R->setName("R");
    R->addColumns("A", "B");
    R->insertRows({{"1", "2", ""},
                   {"2", "2"},
                   {"2", "3"}});

    S = new Relation();
    S->setName("S");
    S->addColumns("B", "C");
    S->insertRows({{"2", "2", ""},
                   {"2", "3"},
                   {"4", "2"},
                   {"5", "5"}});

    result = R->Union(S);
    std::cout << "TEST 8: " << ((*result == *test8) ? "PASSED" : "FAILED") << std::endl;
    std::cout << *result << std::endl;

    delete R;
    delete S;
    delete result;

    // Test case 9: Union test large multiple columns, tables are identical and contains many multiples
    R = new Relation();
    R->setName("R");
    R->addColumns("A", "B", "C");
    R->insertRows({{"1", "2", "3"},
                   {"2", "2", "5"},
                   {"2", "3", "8"},
                   {"2", "2", "5"},
                   {"2", "3", "8"},
                   {"2", "2", "6"},
                   {"2", "3", "8"},
                   {"2", "2", "6"},
                   {"2", "3", "8"},
                   {"2", "2", "8"},
                   {"2", "3", "9"},
                   {"2", "2", "8"},
                   {"2", "3", "9"}});

    S = new Relation();
    S->setName("S");
    S->addColumns("A", "B", "C");
    S->insertRows({{"1", "2", "3"},
                   {"2", "2", "5"},
                   {"2", "3", "8"},
                   {"2", "2", "5"},
                   {"2", "3", "8"},
                   {"2", "2", "6"},
                   {"2", "3", "8"},
                   {"2", "2", "6"},
                   {"2", "3", "8"},
                   {"2", "2", "8"},
                   {"2", "3", "9"},
                   {"2", "2", "8"},
                   {"2", "3", "9"}});

    result = R->Union(S);
    std::cout << "TEST 9: " << ((*result == *test9) ? "PASSED" : "FAILED") << std::endl;
    std::cout << *result << std::endl;

    delete R;
    delete S;
    delete result;

    // Test case 10: Columns are not in order
    R = new Relation();
    R->setName("R");
    R->addColumns("A", "B", "C", "D");
    R->insertRows({{"1", "2", "3", "4"},
                   {"2", "2", "2", "2"},
                   {"2", "3", "2", "3"}});

    S = new Relation();
    S->setName("S");
    S->addColumns("B", "C", "A", "D");
    S->insertRows({{"2", "3", "1", "4"},
                   {"2", "2", "2", "2"},
                   {"3", "2", "2", "3"}});

    result = R->Union(S);
    std::cout << "TEST 10: " << ((*result == *test10) ? "PASSED" : "FAILED") << std::endl;
    std::cout << *result << std::endl;

    delete R;
    delete S;
    delete result;


    delete test1;
    delete test2;
    delete test3;
    delete test4;
    delete test5;
    delete test6;
    delete test7;
    delete test8;
    delete test9;
    delete test10;

    return 0;
}
