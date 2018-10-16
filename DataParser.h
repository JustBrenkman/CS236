/*
Ben Brenkman, Section 3, JustBrenkman@gmail.com
Purpose: Creates a list of inputs based on the input file
*/

#ifndef LAB2_DATAPARSER_H
#define LAB2_DATAPARSER_H

#include "LexicalAnalyzer.h"
#include "Grammar.h"
#include "GrammarException.h"

class DataParser {
private:
    LexicalAnalyzer* lexicalAnalyzer;
    Grammar<LexicalAnalyzer::TOKEN>* datalogGrammar;
    std::vector<Grammar<LexicalAnalyzer::TOKEN> *> listOfGrammars; // This will keep track of the grammars
public:
    explicit DataParser(LexicalAnalyzer* lexicalAnalyzer);

    void checkValidity();

    void clean();

    ~DataParser();
};


#endif //LAB2_DATAPARSER_H
