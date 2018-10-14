//
// Created by bbrenk on 10/5/18.
//

#include "DataParser.h"

#define CREATE_GRAMMAR Grammar<LexicalAnalyzer::TOKEN>::createGrammar
#define CREATE_TERM Grammar<LexicalAnalyzer::TOKEN>::createTerm()
#define TERMINAL_ Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::TERMINAL
#define NON_TERMINAL Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::GRAMMAR

DataParser::DataParser(LexicalAnalyzer *lexicalAnalyzer) {
    this->lexicalAnalyzer = lexicalAnalyzer;

    // Define the grammars
    datalogGrammar = CREATE_GRAMMAR("datalog");
    auto scheme = CREATE_GRAMMAR("scheme");
    auto schemeList = CREATE_GRAMMAR("schemeList");
    auto idList = CREATE_GRAMMAR("idList");
    auto fact = CREATE_GRAMMAR("fact");
    auto factList = CREATE_GRAMMAR("factList");
    auto rule = CREATE_GRAMMAR("rule");
    auto ruleList = CREATE_GRAMMAR("ruleList");
    auto headPredicate = CREATE_GRAMMAR("headPredicate");
    auto predicate = CREATE_GRAMMAR("predicate");
    auto predicateList = CREATE_GRAMMAR("predicateList");
    auto parameter = CREATE_GRAMMAR("parameter");
    auto parameterList = CREATE_GRAMMAR("parameterList");
    auto expression = CREATE_GRAMMAR("expression");
    auto operatorG = CREATE_GRAMMAR("operatorG");
    auto query = CREATE_GRAMMAR("query");
    auto queryList = CREATE_GRAMMAR("queryList");
    auto stringList = CREATE_GRAMMAR("stringList");

    // Define the lambda terminal
    auto term_Lambda = CREATE_TERM;
    term_Lambda->addEntry(TERMINAL_, LexicalAnalyzer::EOF_TOKEN, nullptr);

    //define the terms of the datalog grammar
    auto term_datalog = CREATE_TERM;
    term_datalog->addEntry(TERMINAL_, LexicalAnalyzer::SCHEMES, nullptr);
    term_datalog->addEntry(TERMINAL_, LexicalAnalyzer::COLON, nullptr);
    term_datalog->addEntry(NON_TERMINAL, LexicalAnalyzer::UNDEFINED, scheme);
    term_datalog->addEntry(NON_TERMINAL, LexicalAnalyzer::UNDEFINED, schemeList);
    term_datalog->addEntry(TERMINAL_, LexicalAnalyzer::FACTS, nullptr);
    term_datalog->addEntry(TERMINAL_, LexicalAnalyzer::COLON, nullptr);
    term_datalog->addEntry(NON_TERMINAL, LexicalAnalyzer::UNDEFINED, factList);
    term_datalog->addEntry(TERMINAL_, LexicalAnalyzer::RULES, nullptr);
    term_datalog->addEntry(TERMINAL_, LexicalAnalyzer::COLON, nullptr);
    term_datalog->addEntry(NON_TERMINAL, LexicalAnalyzer::UNDEFINED, ruleList);
    term_datalog->addEntry(TERMINAL_, LexicalAnalyzer::QUERIES, nullptr);
    term_datalog->addEntry(TERMINAL_, LexicalAnalyzer::COLON, nullptr);
    term_datalog->addEntry(NON_TERMINAL, LexicalAnalyzer::UNDEFINED, query);
    term_datalog->addEntry(NON_TERMINAL, LexicalAnalyzer::UNDEFINED, queryList);
    datalogGrammar->addTermToGrammar(term_datalog); // Add term to datalog

    //define terms of scheme
    auto term_scheme = CREATE_TERM;
    term_scheme->addEntry(TERMINAL_, LexicalAnalyzer::ID, nullptr);
    term_scheme->addEntry(TERMINAL_, LexicalAnalyzer::LEFT_PARAM, nullptr);
    term_scheme->addEntry(TERMINAL_, LexicalAnalyzer::ID, nullptr);
    term_scheme->addEntry(NON_TERMINAL, LexicalAnalyzer::UNDEFINED, idList);
    term_scheme->addEntry(TERMINAL_, LexicalAnalyzer::RIGHT_PARAM, nullptr);
    scheme->addTermToGrammar(term_scheme); // Add term to scheme grammar

    auto term_schemeList = CREATE_TERM;
    term_schemeList->addEntry(NON_TERMINAL, LexicalAnalyzer::UNDEFINED, scheme);
    term_schemeList->addEntry(NON_TERMINAL, LexicalAnalyzer::UNDEFINED, schemeList);
    schemeList->addTermToGrammar(term_schemeList);
    schemeList->addLambdaTerm();
//    schemeList->addTermToGrammar(term_Lambda);


    //define terms of idList
    auto term_idList = CREATE_TERM;
    term_idList->addEntry(TERMINAL_, LexicalAnalyzer::COMMA, nullptr);
    term_idList->addEntry(TERMINAL_, LexicalAnalyzer::ID, nullptr);
    term_idList->addEntry(NON_TERMINAL, LexicalAnalyzer::UNDEFINED, idList);
    idList->addTermToGrammar(term_idList);
    idList->addLambdaTerm();
//    idList->addTermToGrammar(term_Lambda);

    // define terms of facts
    auto term_fact = CREATE_TERM;
    term_fact->addEntry(TERMINAL_, LexicalAnalyzer::ID, nullptr);
    term_fact->addEntry(TERMINAL_, LexicalAnalyzer::LEFT_PARAM, nullptr);
    term_fact->addEntry(TERMINAL_, LexicalAnalyzer::STRING, nullptr);
    term_fact->addEntry(NON_TERMINAL, LexicalAnalyzer::UNDEFINED, stringList);
    term_fact->addEntry(TERMINAL_, LexicalAnalyzer::RIGHT_PARAM, nullptr);
    term_fact->addEntry(TERMINAL_, LexicalAnalyzer::PERIOD, nullptr);
    fact->addTermToGrammar(term_fact);

    // define terms of fact list
    auto term_factList = CREATE_TERM;
    term_factList->addEntry(NON_TERMINAL, LexicalAnalyzer::UNDEFINED, fact);
    term_factList->addEntry(NON_TERMINAL, LexicalAnalyzer::UNDEFINED, factList);
    factList->addTermToGrammar(term_factList);
    factList->addLambdaTerm();
//    factList->addTermToGrammar(term_Lambda);

    // define terms of rule
    auto term_rule = CREATE_TERM;
    term_rule->addEntry(NON_TERMINAL, LexicalAnalyzer::UNDEFINED, headPredicate);
    term_rule->addEntry(TERMINAL_, LexicalAnalyzer::COLON_DASH, nullptr);
    term_rule->addEntry(NON_TERMINAL, LexicalAnalyzer::UNDEFINED, predicate);
    term_rule->addEntry(NON_TERMINAL, LexicalAnalyzer::UNDEFINED, predicateList);
    term_rule->addEntry(TERMINAL_, LexicalAnalyzer::PERIOD, nullptr);
    rule->addTermToGrammar(term_rule);

    // define terms of ruleList
    auto term_ruleList = CREATE_TERM;
    term_ruleList->addEntry(NON_TERMINAL, LexicalAnalyzer::UNDEFINED, rule);
    term_ruleList->addEntry(NON_TERMINAL, LexicalAnalyzer::UNDEFINED, ruleList);
    ruleList->addTermToGrammar(term_ruleList);
    ruleList->addLambdaTerm();
//    ruleList->addTermToGrammar(term_Lambda);

    // define terms for head predicate
    auto term_headPredicate = CREATE_TERM;
    term_headPredicate->addEntry(TERMINAL_, LexicalAnalyzer::ID, nullptr);
    term_headPredicate->addEntry(TERMINAL_, LexicalAnalyzer::LEFT_PARAM, nullptr);
    term_headPredicate->addEntry(TERMINAL_, LexicalAnalyzer::ID, nullptr);
    term_headPredicate->addEntry(NON_TERMINAL, LexicalAnalyzer::UNDEFINED, idList);
    term_headPredicate->addEntry(TERMINAL_, LexicalAnalyzer::RIGHT_PARAM, nullptr);
    headPredicate->addTermToGrammar(term_headPredicate);

    // define terms for predicate
    auto term_predicate = CREATE_TERM;
    term_predicate->addEntry(TERMINAL_, LexicalAnalyzer::ID, nullptr);
    term_predicate->addEntry(TERMINAL_, LexicalAnalyzer::LEFT_PARAM, nullptr);
    term_predicate->addEntry(NON_TERMINAL, LexicalAnalyzer::UNDEFINED, parameter);
    term_predicate->addEntry(NON_TERMINAL, LexicalAnalyzer::UNDEFINED, parameterList);
    term_predicate->addEntry(TERMINAL_, LexicalAnalyzer::RIGHT_PARAM, nullptr);
    predicate->addTermToGrammar(term_predicate);

    // define terms for predicateList
    auto term_predicateList = CREATE_TERM;
    term_predicateList->addEntry(TERMINAL_, LexicalAnalyzer::COMMA, nullptr);
    term_predicateList->addEntry(NON_TERMINAL, LexicalAnalyzer::UNDEFINED, predicate);
    term_predicateList->addEntry(NON_TERMINAL, LexicalAnalyzer::UNDEFINED, predicateList);
    predicateList->addTermToGrammar(term_predicateList);
    predicateList->addLambdaTerm();
//    predicateList->addTermToGrammar(term_Lambda);

    // define terms for parameter
    auto term_parameter_string = CREATE_TERM;
    auto term_parameter_id = CREATE_TERM;
    auto term_parameter_expression = CREATE_TERM;
    term_parameter_string->addEntry(TERMINAL_, LexicalAnalyzer::STRING, nullptr);
    term_parameter_id->addEntry(TERMINAL_, LexicalAnalyzer::ID, nullptr);
    term_parameter_expression->addEntry(NON_TERMINAL, LexicalAnalyzer::UNDEFINED, expression);
    parameter->addTermToGrammar(term_parameter_string);
    parameter->addTermToGrammar(term_parameter_id);
    parameter->addTermToGrammar(term_parameter_expression);

    // define terms of parameterList
    auto term_parameterList = CREATE_TERM;
    term_parameterList->addEntry(TERMINAL_, LexicalAnalyzer::COMMA, nullptr);
    term_parameterList->addEntry(NON_TERMINAL, LexicalAnalyzer::UNDEFINED, parameter);
    term_parameterList->addEntry(NON_TERMINAL, LexicalAnalyzer::UNDEFINED, parameterList);
    parameterList->addTermToGrammar(term_parameterList);
    parameterList->addLambdaTerm();
//    parameterList->addTermToGrammar(term_Lambda);

    // define terms of expression
    auto term_expression = CREATE_TERM;
    term_expression->addEntry(TERMINAL_, LexicalAnalyzer::LEFT_PARAM, nullptr);
    term_expression->addEntry(NON_TERMINAL, LexicalAnalyzer::UNDEFINED, parameter);
    term_expression->addEntry(NON_TERMINAL, LexicalAnalyzer::UNDEFINED, operatorG);
    term_expression->addEntry(NON_TERMINAL, LexicalAnalyzer::UNDEFINED, parameter);
    term_expression->addEntry(TERMINAL_, LexicalAnalyzer::RIGHT_PARAM, nullptr);
    expression->addTermToGrammar(term_expression);

    // define operatorG terms
    auto term_operator_add = CREATE_TERM;
    auto term_operator_mult = CREATE_TERM;
    term_operator_add->addEntry(TERMINAL_, LexicalAnalyzer::ADD, nullptr);
    term_operator_mult->addEntry(TERMINAL_, LexicalAnalyzer::MULTIPLY, nullptr);
    operatorG->addTermToGrammar(term_operator_add);
    operatorG->addTermToGrammar(term_operator_mult);

    // define terms of query
    auto term_query = CREATE_TERM;
    term_query->addEntry(NON_TERMINAL, LexicalAnalyzer::UNDEFINED, predicate);
    term_query->addEntry(TERMINAL_, LexicalAnalyzer::Q_MARK, nullptr);
    query->addTermToGrammar(term_query);

    // define terms of queryList
    auto term_queryList = CREATE_TERM;
    term_queryList->addEntry(NON_TERMINAL, LexicalAnalyzer::UNDEFINED, query);
    term_queryList->addEntry(NON_TERMINAL, LexicalAnalyzer::UNDEFINED, queryList);
    queryList->addTermToGrammar(term_queryList);
    queryList->addLambdaTerm();
//    queryList->addTermToGrammar(term_Lambda);

    //define terms of stringlist
    auto term_stringList = CREATE_TERM;
    term_stringList->addEntry(TERMINAL_, LexicalAnalyzer::COMMA, nullptr);
    term_stringList->addEntry(TERMINAL_, LexicalAnalyzer::STRING, nullptr);
    term_stringList->addEntry(NON_TERMINAL, LexicalAnalyzer::UNDEFINED, stringList);
    stringList->addTermToGrammar(term_stringList);
    stringList->addLambdaTerm();
}

DataParser::~DataParser() = default;

// Checks everything and see it it all works out.
void DataParser::checkValidity() {

    // Gets a list of tokens from sexy lexy
    std::vector<LexicalAnalyzer::token_struct> listOfTokens = lexicalAnalyzer->getTokenList();
    std::vector<LexicalAnalyzer::TOKEN> tokens;
    // Some fancy string code
    tokens.reserve(listOfTokens.size()); // Just make sure that we minimize vector allocation time
    for (auto &p : listOfTokens) {
        // Get a proper token list
        tokens.push_back(p.token);
    }

    // Add that eof token, lol we don't actually need it
    tokens.push_back(LexicalAnalyzer::EOF_TOKEN);

    int index = 0;
    try {

        // Give the grammar our list, see if it works. Fingers crossed
        datalogGrammar->proccessList(tokens, index);

        // Double check to make sure nothing was left out, dem tokens have some serious FOMO
        if (index < tokens.size() && tokens.at(static_cast<unsigned long>(index)) != LexicalAnalyzer::EOF_TOKEN)
            throw GrammarException(index, "", "");
        std::cout << "Successful!" << std::endl; // If it finishes with no problem it was successful

        // Create our list of schemes and such

    } catch (std::string &e) {
        std::cout << "Failed: " << e << index << std::endl;
    } catch (GrammarException &grammarException) {
        // Just checking for those failed terms
        std::cout << "Failure!" << std::endl;
        std::string token = LexicalAnalyzer::enumToString(
                listOfTokens.at(static_cast<unsigned long>(grammarException.getIndex())).token);
        int lineNumber = listOfTokens.at(static_cast<unsigned long>(grammarException.getIndex())).lineNumber;
        std::string tokenStr = listOfTokens.at(static_cast<unsigned long>(grammarException.getIndex())).tokenStr;
        std::cout << "(" << token << ", \"" << tokenStr << "\", " << lineNumber << ")" << std::endl;
    }

}

// calls the grammars clean function before deleting the pointers
void DataParser::clean() {
    for (auto &grammar : listOfGrammars) {
        grammar->clean();
        delete grammar;
    }
}
