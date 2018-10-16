//
// Created by bbrenk on 10/13/18.
//

#include "Queries.h"

Queries::Queries(std::vector<LexicalAnalyzer::token_struct> &list, unsigned int &index) {
    Utilities::checkFor(list, LexicalAnalyzer::QUERIES, index);
    Utilities::checkFor(list, LexicalAnalyzer::COLON, index);

    do {
        queries.push_back(new Query(list, index));
        if (index >= list.size()) break;
    } while (list.at(index).token != LexicalAnalyzer::ID);
}

void Queries::clean() {
    for (auto &q : queries) {
        q->clean();
        delete q;
    }
}

