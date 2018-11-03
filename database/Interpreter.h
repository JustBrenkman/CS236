//
// Created by bbrenk on 11/2/18.
//

#ifndef LAB3_INTERPRETER_H
#define LAB3_INTERPRETER_H


#include "../Facts.h"
#include "Queries.h"
#include "../Schemes.h"
#include "Relation.h"

class Interpreter {
private:
    std::vector<Relation> relations;
public:
//    Interpreter();
    ~Interpreter();

    static Interpreter *generateRelations(Schemes &schemes, Facts &facts);

    static void proccessQueries(Interpreter *interpreter, Queries queries);

    friend std::ostream &operator<<(std::ostream &os, Interpreter &interpreter);
};


#endif //LAB3_INTERPRETER_H
