//
// Created by bbrenk on 10/15/18.
//

#include "Fact.h"

Fact::Fact(std::vector<LexicalAnalyzer::token_struct> &list, unsigned int &index) {
    id = new Id(list, index);

    Utilities::checkFor(list, LexicalAnalyzer::LEFT_PARAM, index);

    while (true) {
        listOfStrings.push_back(new DLString(list, index));
        if (list.at(index).token != LexicalAnalyzer::COMMA) break;
        index++;
    }

    Utilities::checkFor(list, LexicalAnalyzer::RIGHT_PARAM, index);
    Utilities::checkFor(list, LexicalAnalyzer::PERIOD, index);
}

std::vector<std::string> Fact::listTheStrings() {
    std::vector<std::string> strings;

    for (auto &p : listOfStrings)
        strings.push_back(p->toString());

    return strings;
}

void Fact::clean() {
    delete id;
    for (auto &a : listOfStrings) {
        delete a;
    }
}

std::string Fact::getName() {
    return id->toString();
}

