//
// Created by bbrenk on 10/15/18.
//

#include "Utilities.h"

void
Utilities::checkFor(std::vector<LexicalAnalyzer::TOKEN> *list, LexicalAnalyzer::TOKEN tokenType, unsigned int index) {
    checkType(list, tokenType, index);
    index++;
}

void
Utilities::checkType(std::vector<LexicalAnalyzer::TOKEN> *list, LexicalAnalyzer::TOKEN tokenType, unsigned int index) {
    if (list->at(index) == tokenType) {

    }
}
