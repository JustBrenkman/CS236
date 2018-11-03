//
// Created by bbrenk on 10/15/18.
//

#include "Id.h"

Id::Id(std::vector<LexicalAnalyzer::token_struct> &list, unsigned int &index) {
    Utilities::checkType(list, LexicalAnalyzer::ID, index);
    id = list.at(index).tokenStr;
    index++;
}

std::string Id::toString() const {
    return id;
}
