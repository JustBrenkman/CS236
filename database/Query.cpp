//
// Created by bbrenk on 10/15/18.
//

#include "Query.h"

Query::Query(std::vector<LexicalAnalyzer::token_struct> &list, unsigned int &index) : Predicate(list, index) {
    Utilities::checkFor(list, LexicalAnalyzer::Q_MARK, index);
}
