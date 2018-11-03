//
// Created by bbrenk on 10/15/18.
//

#include "Query.h"

Query::Query(std::vector<LexicalAnalyzer::token_struct> &list, unsigned int &index) : Predicate(list, index) {
    Utilities::checkFor(list, LexicalAnalyzer::Q_MARK, index);
}

std::string Query::getName() {
    return id->toString();
}

std::vector<std::string> Query::getParams() {
    std::vector<std::string> list;
    for (auto &p : parameters) {
        list.push_back(p->toString());
    }
    return list;
}
