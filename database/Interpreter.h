//
// Created by bbrenk on 11/2/18.
//

#ifndef LAB3_INTERPRETER_H
#define LAB3_INTERPRETER_H


#include "Facts.h"
#include "Queries.h"
#include "Schemes.h"
#include "Relation.h"
#include "../lab4/Rules.h"

class Interpreter {
private:

protected:
    std::vector<Relation *> relations;

    void addRelation(Relation *relation);

    void printResults(Query *query, Relation *table);

    Relation *proccessQueryOnTable(Query *query, Relation *table);
    Relation *proccessPredicateOnTable(Predicate *query, Relation *table);

    Relation *renameAndProject(Query *query, Relation *table);
    void processRule(Relation* table, Rule *rule);
public:
//    Interpreter();
    ~Interpreter();

    static Interpreter *generateRelations(Schemes &schemes, Facts &facts, Rules &rules);

    static void proccessQueries(Interpreter *interpreter, Queries queries);

    friend std::ostream &operator<<(std::ostream &os, Interpreter &interpreter);

    void clean();
};


#endif //LAB3_INTERPRETER_H
