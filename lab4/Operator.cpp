//
// Created by bbrenk on 10/15/18.
//

#include "Operator.h"

Operator::Operator(std::vector<LexicalAnalyzer::token_struct> &list, unsigned int &index) {
    switch (list.at(index).token) {
        case LexicalAnalyzer::TOKEN::ADD:
            operatorG = list.at(index).token;
            break;
        case LexicalAnalyzer::TOKEN::MULTIPLY:
            operatorG = list.at(index).token;
            break;
        default:
            throw GrammarException(index, LexicalAnalyzer::enumToString(list.at(index).token), "");
    }
    index++;
}

std::string Operator::toString() const {
    return operatorG == LexicalAnalyzer::ADD ? "+" : "*";
}
