//
// Created by bbrenk on 10/15/18.
//

#ifndef LAB2_QUERY_H
#define LAB2_QUERY_H

#include "Predicate.h"

class Query : public Predicate {
public:
    Query(std::vector<LexicalAnalyzer::token_struct> &list, unsigned int &index);
};


#endif //LAB2_QUERY_H
