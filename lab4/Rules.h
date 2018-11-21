//
// Created by bbrenk on 10/13/18.
//

#ifndef LAB2_RULES_H
#define LAB2_RULES_H


#include "Rule.h"

class Rules {
private:
    std::vector<Rule *> rules;

public:
    Rules(std::vector<LexicalAnalyzer::token_struct> &list, unsigned int &index);

    friend std::ostream &operator<<(std::ostream &os, const Rules &facts1) {
        os << "Rules(" << facts1.rules.size() << "):" << std::endl;
        for (auto &a: facts1.rules) {
            os << "  " << *a << std::endl;
        }
        return os;
    }

    std::vector<Rule*> getRules() { return rules; };
    void clean();
};


#endif //LAB2_RULES_H
