//
// Created by bbrenk on 10/5/18.
//

#include "DataParser.h"

DataParser::DataParser(LexicalAnalyzer* lexicalAnalyzer) {
    this->lexicalAnalyzer = lexicalAnalyzer;

    // Create the tokens
    auto term = Grammar<LexicalAnalyzer::TOKEN >::createTerm();
    auto term1 = Grammar<LexicalAnalyzer::TOKEN >::createTerm();
    auto term2 = Grammar<LexicalAnalyzer::TOKEN>::createTerm();

    // Create grammar and define it with the terms created above
    Grammar<LexicalAnalyzer::TOKEN> *number = Grammar<LexicalAnalyzer::TOKEN>::createGrammar();
    term->addEntry(Grammar<LexicalAnalyzer::TOKEN >::Term<LexicalAnalyzer::TOKEN >::TERM_SINGLE, LexicalAnalyzer::ID, nullptr);
    term2->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::EPSOLON, LexicalAnalyzer::EOF_TOKEN,
                    nullptr);
    term->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::GRAMMAR, LexicalAnalyzer::UNDEFINED,
                   number);
    number->addTermToGrammar(term);
    number->addTermToGrammar(term2);

    datalogGrammar = Grammar<LexicalAnalyzer::TOKEN>::createGrammar();
    term1->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::TERM_SINGLE,
                    LexicalAnalyzer::SCHEMES, nullptr);
    term1->addEntry(Grammar<LexicalAnalyzer::TOKEN >::Term<LexicalAnalyzer::TOKEN >::GRAMMAR, LexicalAnalyzer::UNDEFINED, number);
    datalogGrammar->addTermToGrammar(term1);
}

DataParser::~DataParser() = default;

void DataParser::checkValidity() {
    std::vector<LexicalAnalyzer::token_struct> listOfTokens = lexicalAnalyzer->getTokenList();

    for (auto &p : listOfTokens) {
        std::cout << "Processing token: " << lexicalAnalyzer->enumToString(p.token) << std::endl;
        datalogGrammar->proccessTerm(p.token);
    }

    std::cout << "Successful!" << std::endl;
}
