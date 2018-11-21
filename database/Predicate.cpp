//
// Created by bbrenk on 10/15/18.
//

#include "Predicate.h"

Predicate::Predicate(std::vector<LexicalAnalyzer::token_struct> &list, unsigned int &index) {
    id = new Id(list, index);
    Utilities::checkFor(list, LexicalAnalyzer::LEFT_PARAM, index);

    while (true) {
        parameters.push_back(Parameter::createParameter(list, index));
        if (list.at(index).token != LexicalAnalyzer::COMMA) break;
        index++;
    }

    Utilities::checkFor(list, LexicalAnalyzer::RIGHT_PARAM, index);
}

void Predicate::clean() {
    delete id;

    for (auto &p : parameters) {
        p->clean();
        delete p;
    }
}

std::vector<std::string> Predicate::getParams() {
    std::vector<std::string> list;
    for (auto &p : parameters) {
        list.push_back(p->toString());
    }
    return list;
}
