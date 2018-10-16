//
// Created by bbrenk on 10/15/18.
//

#ifndef LAB2_ID_H
#define LAB2_ID_H

#include "Parameter.h"

class Id : public Parameter {
private:
    std::string id;
public:
    Id(std::vector<LexicalAnalyzer::token_struct> &list, unsigned int &index);

    friend std::ostream &operator<<(std::ostream &os, const Id &id) {
        os << id.id;
        return os;
    }

    std::string toString() const override;

    void clean() override {};
};


#endif //LAB2_ID_H
