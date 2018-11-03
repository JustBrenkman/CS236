//
// Created by bbrenk on 10/15/18.
//

#ifndef LAB2_PARAMETER_H
#define LAB2_PARAMETER_H


#include <vector>
#include "LexicalAnalyzer.h"
#include "Utilities.h"

class Parameter {
public:
public:
    static bool inInFirstOf(std::vector<LexicalAnalyzer::token_struct> &list, LexicalAnalyzer::TOKEN tokenType,
                            unsigned int &index);

    Parameter();

    static Parameter *createParameter(std::vector<LexicalAnalyzer::token_struct> &list, unsigned int &index);

    virtual std::string toString() const;

    virtual void clean();

    friend std::ostream &operator<<(std::ostream &os, const Parameter &rule) {
        os << rule.toString() << "";
        return os;
    }

    virtual ~Parameter();
};


#endif //LAB2_PARAMETER_H
