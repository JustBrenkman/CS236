//
// Created by bbrenk on 10/15/18.
//

#ifndef LAB2_RULE_H
#define LAB2_RULE_H

#include "HeadPredicate.h"
#include "Predicate.h"

class Rule {
private:
    HeadPredicate *headPredicate;
    std::vector<Predicate *> predicate;
public:
    Rule(std::vector<LexicalAnalyzer::token_struct> &list, unsigned int &index);

    friend std::ostream &operator<<(std::ostream &os, const Rule &rule) {
        os << *rule.headPredicate << " :- ";

        if (!rule.predicate.empty()) {
            for (unsigned int i = 0; i < rule.predicate.size() - 1; i++) {
                os << *rule.predicate.at(i) << ",";
            }

            os << *rule.predicate.at(rule.predicate.size() - 1) << ".";
        }

        return os;
    }

    void clean();
};


#endif //LAB2_RULE_H
