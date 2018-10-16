//
// Created by bbrenk on 10/15/18.
//

#ifndef LAB2_DLSTRING_H
#define LAB2_DLSTRING_H

#include "Parameter.h"

class DLString : public Parameter {
public:
    std::string constant;

    DLString(std::vector<LexicalAnalyzer::token_struct> &list, unsigned int &index);

    friend std::ostream &operator<<(std::ostream &os, const DLString &string) {
        os << string.constanti;
        return os;
    }

    std::string toString() const override;

    void clean() override {};
};


#endif //LAB2_DLSTRING_H
