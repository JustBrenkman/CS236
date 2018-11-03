//
// Created by bbrenk on 10/15/18.
//

#include "Rule.h"

Rule::Rule(std::vector<LexicalAnalyzer::token_struct> &list, unsigned int &index) : predicate() {
    headPredicate = new HeadPredicate(list, index);
    Utilities::checkFor(list, LexicalAnalyzer::COLON_DASH, index);

    while (true) {
        predicate.push_back(new Predicate(list, index));
        if (list.at(index).token != LexicalAnalyzer::COMMA) break;
        index++;
    }

    Utilities::checkFor(list, LexicalAnalyzer::PERIOD, index);
}

void Rule::clean() {
    headPredicate->clean();
    delete headPredicate;

    for (auto &p : predicate) {
        p->clean();
        delete p;
    }
}
