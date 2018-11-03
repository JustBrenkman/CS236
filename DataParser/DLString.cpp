//
// Created by bbrenk on 10/15/18.
//

#include "DLString.h"

DLString::DLString(std::vector<LexicalAnalyzer::token_struct> &list, unsigned int &index) {
    Utilities::checkType(list, LexicalAnalyzer::STRING, index);

    constant = list.at(index).tokenStr;
    index++;
}

std::string DLString::toString() const {
    return constant;
}
