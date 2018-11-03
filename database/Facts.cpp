//
// Created by bbrenk on 10/13/18.
//

#include "Facts.h"
#include "Domain.h"

Facts::Facts(std::vector<LexicalAnalyzer::token_struct> &list, unsigned int &index) {
    Utilities::checkFor(list, LexicalAnalyzer::FACTS, index);
    Utilities::checkFor(list, LexicalAnalyzer::COLON, index);

    while (list.at(index).token == LexicalAnalyzer::ID) {
        facts.push_back(new Fact(list, index));
    }
}

std::string Facts::toDomain() {
    Domain domain;

    for (auto &f : facts) {
        for (auto &s : f->listTheStrings())
            domain.addStringToDomain(s);
    }

    return domain.toString();
}

void Facts::clean() {
    for (auto &f : facts) {
        f->clean();
        delete f;
    }
}

std::vector<Fact *> Facts::getFacts() {
    return facts;
}

