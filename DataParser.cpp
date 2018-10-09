//
// Created by bbrenk on 10/5/18.
//

#include "DataParser.h"

DataParser::DataParser(LexicalAnalyzer* lexicalAnalyzer) {
    lexicalAnalyzer = lexicalAnalyzer;

    auto term = Grammar<LexicalAnalyzer::TOKEN >::createTerm();
    auto term1 = Grammar<LexicalAnalyzer::TOKEN >::createTerm();

    term->addEntry(Grammar<LexicalAnalyzer::TOKEN >::Term<LexicalAnalyzer::TOKEN >::TERM_SINGLE, LexicalAnalyzer::ID, nullptr);
    Grammar<LexicalAnalyzer::TOKEN >* number = Grammar<LexicalAnalyzer::TOKEN >::createGrammar(term);

    term1->addEntry(Grammar<LexicalAnalyzer::TOKEN >::Term<LexicalAnalyzer::TOKEN >::GRAMMAR, LexicalAnalyzer::UNDEFINED, number);
    datalogGrammar = Grammar<LexicalAnalyzer::TOKEN >::createGrammar(term1);

}

DataParser::~DataParser() {

}

bool DataParser::isValid() {
    return false;
}
