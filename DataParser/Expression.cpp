//
// Created by bbrenk on 10/15/18.
//

#include <sstream>
#include "Expression.h"

Expression::Expression(std::vector<LexicalAnalyzer::token_struct> &list, unsigned int &index) {

    Utilities::checkFor(list, LexicalAnalyzer::LEFT_PARAM, index);

    left = Parameter::createParameter(list, index);
    operatorg = new Operator(list, index);
    right = Parameter::createParameter(list, index);

    Utilities::checkFor(list, LexicalAnalyzer::RIGHT_PARAM, index);
}

std::string Expression::toString() const {
    std::string str;
    str.append("(");
    str.append(left->toString());
    str.append(operatorg->toString());
    str.append(right->toString());
    str.append(")");
    return str;
}

void Expression::clean() {
    left->clean();
    delete left;
    delete operatorg;
    right->clean();
    delete right;
}