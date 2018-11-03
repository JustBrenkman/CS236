//
// Created by bbrenk on 10/15/18.
//

#include "Scheme.h"

Scheme::Scheme(std::vector<LexicalAnalyzer::token_struct> &list, unsigned int &index) {
    id = new Id(list, index);
    Utilities::checkFor(list, LexicalAnalyzer::LEFT_PARAM, index);

    while (true) {
        ids.push_back(new Id(list, index));
        if (list.at(index).token != LexicalAnalyzer::COMMA) break;
        index++;
    }

    Utilities::checkFor(list, LexicalAnalyzer::RIGHT_PARAM, index);
}

void Scheme::clean() {
    delete id;

    for (auto &i : ids) {
        delete i;
    }
}

std::string Scheme::getName() {
    return id->toString();
}

std::vector<std::string> Scheme::getColumnNames() {
    std::vector<std::string> list;
    list.reserve(ids.size());
    for (auto &i : ids) { list.push_back(i->toString()); }
    return std::vector<std::string>();
}
