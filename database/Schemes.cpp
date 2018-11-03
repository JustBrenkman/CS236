//
// Created by bbrenk on 10/13/18.
//

#include "Schemes.h"

Schemes::Schemes(std::vector<LexicalAnalyzer::token_struct> &list, unsigned int &index) {
    Utilities::checkFor(list, LexicalAnalyzer::SCHEMES, index);
    Utilities::checkFor(list, LexicalAnalyzer::COLON, index);

    do {
        schemes.push_back(new Scheme(list, index));
    } while (list.at(index).token == LexicalAnalyzer::ID);
}

void Schemes::clean() {
    for (auto &s : schemes) {
        s->clean();
        delete s;
    }

}
