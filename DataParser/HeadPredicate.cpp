//
// Created by bbrenk on 10/15/18.
//

#include "HeadPredicate.h"

HeadPredicate::HeadPredicate(std::vector<LexicalAnalyzer::token_struct> &list, unsigned int &index) {

    id = new Id(list, index);
    Utilities::checkFor(list, LexicalAnalyzer::LEFT_PARAM, index);

    while (true) {
        ids.push_back(new Id(list, index));

        if (list.at(index).token != LexicalAnalyzer::COMMA) break;
        index++;
    }

    Utilities::checkFor(list, LexicalAnalyzer::RIGHT_PARAM, index);
}

void HeadPredicate::clean() {
    delete id;

    for (auto &i : ids)
        delete i;

}
