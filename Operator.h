//
// Created by bbrenk on 10/15/18.
//

#ifndef LAB2_OPERATOR_H
#define LAB2_OPERATOR_H


#include "LexicalAnalyzer.h"

class Operator {
private:
    LexicalAnalyzer::TOKEN operatorG;
public:
    Operator(std::vector<LexicalAnalyzer::token_struct> &list, unsigned int &index);

    std::string toString() const;
};


#endif //LAB2_OPERATOR_H
