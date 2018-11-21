////
//// Created by bbrenk on 10/24/18.
////
//
//#include <iostream>
//#include "Relation.h"
//
//void runTestsQuery() {
//    auto test7 = new Relation();
//    auto test8 = new Relation();
//    auto test9 = new Relation();
//    auto test10 = new Relation();
//
//    test7->addColumns("A");
//    test7->insertRows({"a"});
//    test7->insertRows({"b"});
//
//    test8->addColumns("A", "B");
//    test8->insertRows({"b", "c", ""});
//
//    test9->addColumns("X");
//    test9->insertRows({"b"});
//
//    test10->addColumns("A", "B");
//    test10->insertRows({{"a", "c", ""},
//                        {"b", "b", ""},
//                        {"b", "c", ""}});
//
//    /*
//    * Query tests
//    */
//    auto SK = new Relation(); // Setup table
//    SK->setName("SK");
//    SK->addColumns("A", "B");
//    SK->insertRows({{"a", "c"},
//                    {"b", "c"},
//                    {"b", "b"},
//                    {"b", "c", ""}});
//
//    std::cout << *SK << std::endl;
//
//    /*
//     * Test Case: 7 - QUERY
//     * Purpose: tests a series of modifications
//     * SK(A, 'c');
//     */
//    auto project1 = SK->select(std::make_pair("B", "c")); // Select rows where B='c'
//    auto result = project1->project("A"); // prjects the A col, this leaves us with all the possible A values
//    std::cout << "Test Case 7: " << ((*test7 == *result) ? "Success!" : "Fail") << std::endl;
//    std::cout << *result << std::endl;
//
//    delete project1;
//    delete result;
//
//    /*
//    * Test Case: 8 - QUERY
//     * Purpose: tests a series of modifications
//    * SK('b', 'c');
//    */
//    result = SK->select(std::make_pair("A", "b"), std::make_pair("B", "c")); // Select Columns where A='b' and C='c'
//    result->setName("Result");
//    std::cout << "Test Case 8: " << ((*test8 == *result) ? "Success!" : "Fail") << std::endl;
//    std::cout << *result << std::endl;
//    delete result;
//
//    /*
//    * Test Case: 9 - QUERY
//    * Purpose: tests a series of modifications
//    * SK(X, X);
//    */
//    auto table2 = SK->select(std::make_pair("A", "B")); // Get rid of duplicates
//    table2->setName("S");
//    auto table3 = table2->rename(std::make_pair("A", "X")); // Rename column, B as it will have all the values
//    table3->setName("K");
//    result = table3->project("X"); // Project just to have the final results
//    result->setName("Result");
//    std::cout << "Test Case 9: " << ((*test9 == *result) ? "Success!" : "Fail") << std::endl;
//    std::cout << *result << std::endl; // Print table
//
//    delete table2;
//    delete table3;
//    delete result;
//
//    /*
//    * Test Case: 10 - QUERY
//    * Purpose: tests a series of modifications
//    * SK(A, B);
//    */
//    result = SK->project("A", "B"); // Project multiple columns to get all values for A and B
//    result->setName("Result");
//    std::cout << "Test Case 10: " << ((*test10 == *result) ? "Success!" : "Fail") << std::endl;
//    std::cout << *result << std::endl; // Print table
//
//    delete SK;
//    delete result;
//
//    delete test7;
//    delete test8;
//    delete test9;
//    delete test10;
//}
//
//int main(int argc, char **argv) {
//    auto Q = new Relation(); // Setup table
//    Q->setName("Q");
//    Q->addColumns("A", "B", "C");
//    Q->insertRows({{"Bret",     "Mathew", "Johnson"},
//                   {"Benjamin", "Geurt",  "Brenkman"},
//                   {"Kayla",    "?",      "Cooper"},
//                   {"Ben",      "Ben",    "Ben"},
//                   {"Ben",      "Geurt",  "Brenkman"},
//                   {"Bret",     "Bret",   "Cooper"},
//                   {"Kayla",    "Cooper", "Cooper"}});
//
//    std::cout << *Q << std::endl;
//
//    auto test1 = new Relation();
//    auto test2 = new Relation();
//    auto test3 = new Relation();
//    auto test4 = new Relation();
//    auto test5 = new Relation();
//    auto test6 = new Relation();
//
//
//    test1->addColumns("A", "B", "C");
//    test1->insertRows({"Ben", "Geurt", "Brenkman"});
//
//    test2->addColumns("A", "B", "C");
//    test2->insertRows({{"Ben",   "Ben",    "Ben"},
//                       {"Kayla", "Cooper", "Cooper"}});
//
//    test3->addColumns("A", "B", "C");
//    test3->insertRows({"Kayla", "Cooper", "Cooper"});
//
//    test4->addColumns("First Name", "Middle Name", "Last Name");
//    test4->insertRows({{"Ben",      "Ben",    "Ben"},
//                       {"Ben",      "Geurt",  "Brenkman"},
//                       {"Benjamin", "Geurt",  "Brenkman"},
//                       {"Bret",     "Bret",   "Cooper"},
//                       {"Bret",     "Mathew", "Johnson"},
//                       {"Kayla",    "?",      "Cooper"},
//                       {"Kayla",    "Cooper", "Cooper"}});
//
//    test5->addColumns("First Name", "Middle Name", "Last Name");
//    test5->insertRows({"Ben", "Geurt", "Brenkman"});
//
//    test6->addColumns("First Name");
//    test6->insertRows({{"Ben"},
//                       {"Benjamin"},
//                       {"Bret"},
//                       {"Kayla", "", ""}}); // compiler issue
//
//    /*
//    * Test Case: 1 - SELECT
//    * Purpose: Tests select function with two column-value parameters
//     * SELECT * WHERE A='Ben' AND C='Brenkman'
//    */
//    auto R = Q->select(std::make_pair("A", "Ben"), std::make_pair("C", "Brenkman"));
//    R->setName("R");
//    std::cout << "Test Case 1: " << ((*test1 == *R) ? "Success!" : "Fail") << std::endl;
//    std::cout << *R << std::endl;
//
//    /*
//     * Test Case: 2 - SELECT
//     * Purpose: tests select function with col-col comparison
//     * SELECT * WHERE B=C
//     */
//    auto M = Q->select(std::make_pair("B", "C"));
//    M->setName("M");
//    std::cout << "Test Case 2: " << ((*test2 == *M) ? "Success!" : "Fail") << std::endl;
//    std::cout << *M << std::endl;
//
//    /*
//     * Test Case: 3 - SELECT
//     * Purpose: Testing both same column and column value select
//     * SELECT * WHERE A = Kayla AND B=C
//     */
//
//    auto N = Q->select(std::make_pair("A", "Kayla"), std::make_pair("B", "C"));
//    N->setName("N");
//    std::cout << "Test Case 3: " << ((*test3 == *N) ? "Success!" : "Fail") << std::endl;
//    std::cout << *N << std::endl;
//
//    /*
//     * Test Case: 4 - RENAME
//     * Purpose: Tests the rename function on multiple columns
//     * RENAME A='First Name', B='Middle Name', C='Last Name'
//     */
//    auto L = Q->rename(std::make_pair("A", "First Name"), std::make_pair("B", "Middle Name"),
//                       std::make_pair("C", "Last Name"));
//    L->setName("L");
//    std::cout << "Test Case 4: " << ((*test4 == *L) ? "Success!" : "Fail") << std::endl;
//    std::cout << *L << std::endl;
//
//    /*
//     * Test Case: 5 - RENAME
//     * Purpose: Tests the rename function on multiple columns based on a previously modified table
//     * RENAME A='First Name', B='Middle Name', C='Last Name'
//     */
//    auto O = R->rename(std::make_pair("A", "First Name"), std::make_pair("B", "Middle Name"),
//                       std::make_pair("C", "Last Name"));
//    O->setName("L");
//    std::cout << "Test Case 5: " << ((*test5 == *O) ? "Success!" : "Fail") << std::endl;
//    std::cout << *O << std::endl;
//
//    Relation::setPrintCom(Relation::CHAINED);
//
//    /*
//     * Test Case: 6 - PROJECT
//     * Purpose: Projects the table with one column
//     * PROJECT 'First Name'
//     */
//    auto P = L->project("First Name");
//    P->setName("P");
//    std::cout << "Test Case 6: " << ((*test6 == *P) ? "Success!" : "Fail") << std::endl;
//    std::cout << *P << std::endl;
//
//    runTestsQuery();
//
//    delete Q;
//    delete R;
//    delete L;
//    delete M;
//    delete N;
//    delete P;
//    delete O;
//
//    delete test1;
//    delete test2;
//    delete test3;
//    delete test4;
//    delete test5;
//    delete test6;
//
//    return 0;
//}
