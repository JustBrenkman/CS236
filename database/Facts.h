//
// Created by bbrenk on 10/13/18.
//

#ifndef LAB2_FACTS_H
#define LAB2_FACTS_H


#include "Fact.h"

class Facts {
private:
    std::vector<Fact *> facts;

public:
    Facts(std::vector<LexicalAnalyzer::token_struct> &list, unsigned int &index);

    friend std::ostream &operator<<(std::ostream &os, const Facts &facts1) {
        os << "Facts(" << facts1.facts.size() << "):" << std::endl;
        for (auto &a: facts1.facts) {
            os << "  " << *a << std::endl;
        }
        return os;
    }

    std::string toDomain();

    void clean();
};


#endif //LAB2_FACTS_H
