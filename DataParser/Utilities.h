//
// Created by bbrenk on 10/15/18.
//

#ifndef LAB2_UTILITIES_H
#define LAB2_UTILITIES_H

#include "LexicalAnalyzer.h"
#include "GrammarException.h"

class Utilities {
public:
    static void
    checkFor(std::vector<LexicalAnalyzer::token_struct> &list, LexicalAnalyzer::TOKEN tokenType, unsigned int &index);

    static void
    checkType(std::vector<LexicalAnalyzer::token_struct> &list, LexicalAnalyzer::TOKEN tokenType, unsigned int &index);

};


#endif //LAB2_UTILITIES_H
