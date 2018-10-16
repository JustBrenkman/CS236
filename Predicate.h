//
// Created by bbrenk on 10/15/18.
//

#ifndef LAB2_PREDICATE_H
#define LAB2_PREDICATE_H

#include "Id.h"

class Predicate {
private:
    Id *id;
    std::vector<Parameter *> parameters;
public:
    Predicate(std::vector<LexicalAnalyzer::token_struct> &list, unsigned int &index);

    friend std::ostream &operator<<(std::ostream &os, const Predicate &rule) {
        os << *rule.id << "(";

        if (!rule.parameters.empty()) {
            for (unsigned int i = 0; i < rule.parameters.size() - 1; i++) {
                os << *rule.parameters.at(i) << ",";
            }

            os << *rule.parameters.at(rule.parameters.size() - 1) << ")";
        }

        return os;
    }

    void clean();
};


#endif //LAB2_PREDICATE_H
