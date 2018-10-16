//
// Created by bbrenk on 10/13/18.
//

#ifndef LAB2_QUERIES_H
#define LAB2_QUERIES_H


#include "Query.h"

class Queries {
private:
    std::vector<Query *> queries;

public:
    Queries(std::vector<LexicalAnalyzer::token_struct> &list, unsigned int &index);

    friend std::ostream &operator<<(std::ostream &os, const Queries &queries1) {
        os << "Queries(" << queries1.queries.size() << ")" << std::endl;
        for (auto &a: queries1.queries) {
            os << "  " << *a << "?" << std::endl;
        }
        return os;
    }

    void clean();
};


#endif //LAB2_QUERIES_H
