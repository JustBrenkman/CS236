//
// Created by bbrenk on 11/2/18.
//

#include "Interpreter.h"

Interpreter::~Interpreter() = default;

Interpreter *Interpreter::generateRelations(Schemes &schemes, Facts &facts) {
    return nullptr;
}

void Interpreter::proccessQueries(Interpreter *interpreter, Queries queries) {

}

std::ostream &operator<<(std::ostream &os, Interpreter &interpreter) {
    return os;
}
