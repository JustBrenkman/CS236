//
// Created by bbrenk on 10/15/18.
//

#ifndef LAB2_SCHEME_H
#define LAB2_SCHEME_H


#include "Id.h"

class Scheme {
private:
    Id *id;
    std::vector<Id *> ids;

public:
    Scheme(std::vector<LexicalAnalyzer::token_struct> &list, unsigned int &index);

    friend std::ostream &operator<<(std::ostream &os, const Scheme &scheme) {
        os << *scheme.id << "(";

        if (!scheme.ids.empty()) {
            for (unsigned int i = 0; i < scheme.ids.size() - 1; i++) {
                os << *scheme.ids.at(i) << ",";
            }

            os << *scheme.ids.at(scheme.ids.size() - 1) << ")";
        }

        return os;
    }

    void clean();
};


#endif //LAB2_SCHEME_H
