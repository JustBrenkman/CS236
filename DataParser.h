//
// Created by bbrenk on 10/5/18.
//

#ifndef LAB2_DATAPARSER_H
#define LAB2_DATAPARSER_H

#include "LexicalAnalyzer.h"
#include "Grammar.h"

class DataParser {
private:
    LexicalAnalyzer* lexicalAnalyzer;
    Grammar<LexicalAnalyzer::TOKEN>* datalogGrammar;
    std::vector<Grammar<LexicalAnalyzer::TOKEN*>> listOfGrammars; // This will keep track of the grammars

public:
    explicit DataParser(LexicalAnalyzer* lexicalAnalyzer);

    bool isValid();

    ~DataParser();
};


#endif //LAB2_DATAPARSER_H
