//
// Created by bbrenk on 10/15/18.
//

#ifndef LAB2_EXPRESSION_H
#define LAB2_EXPRESSION_H

#include "Parameter.h"
#include "Operator.h"

class Expression : public Parameter {

private:
    Parameter *left;
    Operator *operatorg;
    Parameter *right;

public:
    Expression(std::vector<LexicalAnalyzer::token_struct> &list, unsigned int &index);

    std::string toString() const override;

    void clean() override;
};

#endif //LAB2_EXPRESSION_H
