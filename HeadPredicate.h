//
// Created by bbrenk on 10/15/18.
//

#ifndef LAB2_HEADPREDICATE_H
#define LAB2_HEADPREDICATE_H


#include "Id.h"

class HeadPredicate {
private:
    Id *id;
    std::vector<Id *> ids;

public:
    HeadPredicate(std::vector<LexicalAnalyzer::token_struct> &list, unsigned int &index);

    friend std::ostream &operator<<(std::ostream &os, const HeadPredicate &rule) {
        os << *rule.id << "";

        if (!rule.ids.empty()) {
            for (unsigned int i = 0; i < rule.ids.size() - 1; i++) {
                os << *rule.ids.at(i) << ",";
            }

            os << *rule.ids.at(rule.ids.size() - 1) << ")";
        }

        return os;
    }

    void clean();
};


#endif //LAB2_HEADPREDICATE_H
