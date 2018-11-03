//
// Created by bbrenk on 10/15/18.
//

#include "Utilities.h"

void Utilities::checkFor(std::vector<LexicalAnalyzer::token_struct> &list, LexicalAnalyzer::TOKEN tokenType,
                         unsigned int &index) {
    checkType(list, tokenType, index);
    index++;
}

void Utilities::checkType(std::vector<LexicalAnalyzer::token_struct> &list, LexicalAnalyzer::TOKEN tokenType,
                          unsigned int &index) {
    if (list.at(index).token != tokenType) {
        throw GrammarException(index, LexicalAnalyzer::enumToString(tokenType), "");
    }
}
