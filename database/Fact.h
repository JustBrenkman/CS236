//
// Created by bbrenk on 10/15/18.
//

#ifndef LAB2_FACT_H
#define LAB2_FACT_H

#include "Id.h"
#include "DLString.h"

class Fact {
private:
    Id *id;
    std::vector<DLString *> listOfStrings;

public:
    Fact(std::vector<LexicalAnalyzer::token_struct> &list, unsigned int &index);

    friend std::ostream &operator<<(std::ostream &os, const Fact &fact) {
        os << *fact.id << "(";

        if (!fact.listOfStrings.empty()) {
            for (unsigned int i = 0; i < fact.listOfStrings.size() - 1; i++) {
                os << *fact.listOfStrings.at(i) << ",";
            }

            os << *fact.listOfStrings.at(fact.listOfStrings.size() - 1) << ").";
        }

        return os;
    }

    std::string getName();

//    std::vector<std::string> listOfFacts();
    std::vector<std::string> listTheStrings();

    void clean();
};


#endif //LAB2_FACT_H
