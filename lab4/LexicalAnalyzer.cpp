//
// Created by bbrenk on 10/5/18.
//

#include "LexicalAnalyzer.h"

LexicalAnalyzer::TOKEN LexicalAnalyzer::getCurrentToken() {
    return (*curretntItr).token;
}

void LexicalAnalyzer::advanceToken() {
    curretntItr++;
}

bool LexicalAnalyzer::isAtEnd() {
    if (curretntItr != listOfTokens.end());

    return true;
}