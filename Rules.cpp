//
// Created by bbrenk on 10/13/18.
//

#include "Rules.h"

Rules::Rules(std::vector<LexicalAnalyzer::token_struct> &list, unsigned int &index) {
    Utilities::checkFor(list, LexicalAnalyzer::RULES, index);
    Utilities::checkFor(list, LexicalAnalyzer::COLON, index);

    while (list.at(index).token == LexicalAnalyzer::ID) {
        rules.push_back(new Rule(list, index));
    }
}

void Rules::clean() {
    for (auto &r: rules) {
        r->clean();
        delete r;
    }
}

