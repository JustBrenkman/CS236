//
// Created by bbrenk on 10/5/18.
//

#include "DataParser.h"

DataParser::DataParser(LexicalAnalyzer* lexicalAnalyzer) {
    this->lexicalAnalyzer = lexicalAnalyzer;

//    // Create the tokens
//    auto term = Grammar<LexicalAnalyzer::TOKEN >::createTerm();
//    auto term1 = Grammar<LexicalAnalyzer::TOKEN >::createTerm();
//    auto term2 = Grammar<LexicalAnalyzer::TOKEN>::createTerm();
//
//    // Create grammar and define it with the terms created above
//    Grammar<LexicalAnalyzer::TOKEN> *number = Grammar<LexicalAnalyzer::TOKEN>::createGrammar();
//    term->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::TERMINAL, LexicalAnalyzer::ID,
//                   nullptr);
//    term2->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::TERMINAL, LexicalAnalyzer::EOF_TOKEN,
//                    nullptr);
//    term->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::GRAMMAR, LexicalAnalyzer::UNDEFINED,
//                   number);
//    number->addTermToGrammar(term);
//    number->addTermToGrammar(term2);
//
//    datalogGrammar = Grammar<LexicalAnalyzer::TOKEN>::createGrammar();
//    term1->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::TERMINAL,
//                    LexicalAnalyzer::SCHEMES, nullptr);
//    term1->addEntry(Grammar<LexicalAnalyzer::TOKEN >::Term<LexicalAnalyzer::TOKEN >::GRAMMAR, LexicalAnalyzer::UNDEFINED, number);
//    datalogGrammar->addTermToGrammar(term1);
//
//    listOfGrammars.push_back(datalogGrammar);
//    listOfGrammars.push_back(number);


    // Define the grammars
    datalogGrammar = Grammar<LexicalAnalyzer::TOKEN>::createGrammar("datalog");
    auto scheme = Grammar<LexicalAnalyzer::TOKEN>::createGrammar("scheme");
    auto schemeList = Grammar<LexicalAnalyzer::TOKEN>::createGrammar("schemeList");
    auto idList = Grammar<LexicalAnalyzer::TOKEN>::createGrammar("idList");
    auto fact = Grammar<LexicalAnalyzer::TOKEN>::createGrammar("fact");
    auto factList = Grammar<LexicalAnalyzer::TOKEN>::createGrammar("factList");
    auto rule = Grammar<LexicalAnalyzer::TOKEN>::createGrammar("rule");
    auto ruleList = Grammar<LexicalAnalyzer::TOKEN>::createGrammar("ruleList");
    auto headPredicate = Grammar<LexicalAnalyzer::TOKEN>::createGrammar("headPredicate");
    auto predicate = Grammar<LexicalAnalyzer::TOKEN>::createGrammar("predicate");
    auto predicateList = Grammar<LexicalAnalyzer::TOKEN>::createGrammar("predicateList");
    auto parameter = Grammar<LexicalAnalyzer::TOKEN>::createGrammar("parameter");
    auto parameterList = Grammar<LexicalAnalyzer::TOKEN>::createGrammar("parameterList");
    auto expression = Grammar<LexicalAnalyzer::TOKEN>::createGrammar("expression");
    auto operatorG = Grammar<LexicalAnalyzer::TOKEN>::createGrammar("operatorG");
    auto query = Grammar<LexicalAnalyzer::TOKEN>::createGrammar("query");
    auto queryList = Grammar<LexicalAnalyzer::TOKEN>::createGrammar("queryList");
    auto stringList = Grammar<LexicalAnalyzer::TOKEN>::createGrammar("stringList");

    // Define the lambda terminal
    auto term_Lambda = Grammar<LexicalAnalyzer::TOKEN>::createTerm();
    term_Lambda->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::TERMINAL,
                          LexicalAnalyzer::EOF_TOKEN, nullptr);

    //define the terms of the datalog grammar
    auto term_datalog = Grammar<LexicalAnalyzer::TOKEN>::createTerm();
    term_datalog->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::TERMINAL,
                           LexicalAnalyzer::SCHEMES, nullptr);
    term_datalog->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::TERMINAL,
                           LexicalAnalyzer::COLON, nullptr);
    term_datalog->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::GRAMMAR,
                           LexicalAnalyzer::UNDEFINED, scheme);
    term_datalog->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::GRAMMAR,
                           LexicalAnalyzer::UNDEFINED, schemeList);
    term_datalog->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::TERMINAL,
                           LexicalAnalyzer::FACTS, nullptr);
    term_datalog->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::TERMINAL,
                           LexicalAnalyzer::COLON, nullptr);
    term_datalog->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::GRAMMAR,
                           LexicalAnalyzer::UNDEFINED, factList);
    term_datalog->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::TERMINAL,
                           LexicalAnalyzer::RULES, nullptr);
    term_datalog->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::TERMINAL,
                           LexicalAnalyzer::COLON, nullptr);
    term_datalog->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::GRAMMAR,
                           LexicalAnalyzer::UNDEFINED, ruleList);
    term_datalog->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::TERMINAL,
                           LexicalAnalyzer::QUERIES, nullptr);
    term_datalog->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::TERMINAL,
                           LexicalAnalyzer::COLON, nullptr);
    term_datalog->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::GRAMMAR,
                           LexicalAnalyzer::UNDEFINED, query);
    term_datalog->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::GRAMMAR,
                           LexicalAnalyzer::UNDEFINED, queryList);
    datalogGrammar->addTermToGrammar(term_datalog); // Add term to datalog

    //define terms of scheme
    auto term_scheme = Grammar<LexicalAnalyzer::TOKEN>::createTerm();
    term_scheme->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::TERMINAL, LexicalAnalyzer::ID,
                          nullptr);
    term_scheme->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::TERMINAL,
                          LexicalAnalyzer::LEFT_PARAM, nullptr);
    term_scheme->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::TERMINAL, LexicalAnalyzer::ID,
                          nullptr);
    term_scheme->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::GRAMMAR,
                          LexicalAnalyzer::UNDEFINED, idList);
    term_scheme->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::TERMINAL,
                          LexicalAnalyzer::RIGHT_PARAM, nullptr);
    scheme->addTermToGrammar(term_scheme); // Add term to scheme grammar

    auto term_schemeList = Grammar<LexicalAnalyzer::TOKEN>::createTerm();
    term_schemeList->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::GRAMMAR,
                              LexicalAnalyzer::UNDEFINED, scheme);
    term_schemeList->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::GRAMMAR,
                              LexicalAnalyzer::UNDEFINED, schemeList);
    schemeList->addTermToGrammar(term_schemeList);
    schemeList->addLambdaTerm();
//    schemeList->addTermToGrammar(term_Lambda);


    //define terms of idList
    auto term_idList = Grammar<LexicalAnalyzer::TOKEN>::createTerm();
    term_idList->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::TERMINAL,
                          LexicalAnalyzer::COMMA, nullptr);
    term_idList->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::TERMINAL, LexicalAnalyzer::ID,
                          nullptr);
    term_idList->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::GRAMMAR,
                          LexicalAnalyzer::UNDEFINED, idList);
    idList->addTermToGrammar(term_idList);
    idList->addLambdaTerm();
//    idList->addTermToGrammar(term_Lambda);

    // define terms of facts
    auto term_fact = Grammar<LexicalAnalyzer::TOKEN>::createTerm();
    term_fact->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::TERMINAL, LexicalAnalyzer::ID,
                        nullptr);
    term_fact->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::TERMINAL,
                        LexicalAnalyzer::LEFT_PARAM, nullptr);
    term_fact->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::TERMINAL,
                        LexicalAnalyzer::STRING, nullptr);
    term_fact->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::GRAMMAR,
                        LexicalAnalyzer::UNDEFINED, stringList);
    term_fact->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::TERMINAL,
                        LexicalAnalyzer::RIGHT_PARAM, nullptr);
    term_fact->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::TERMINAL,
                        LexicalAnalyzer::PERIOD, nullptr);
    fact->addTermToGrammar(term_fact);

    // define terms of fact list
    auto term_factList = Grammar<LexicalAnalyzer::TOKEN>::createTerm();
    term_factList->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::GRAMMAR,
                            LexicalAnalyzer::UNDEFINED, fact);
    term_factList->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::GRAMMAR,
                            LexicalAnalyzer::UNDEFINED, factList);
    factList->addTermToGrammar(term_factList);
    factList->addLambdaTerm();
//    factList->addTermToGrammar(term_Lambda);

    // define terms of rule
    auto term_rule = Grammar<LexicalAnalyzer::TOKEN>::createTerm();
    term_rule->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::GRAMMAR,
                        LexicalAnalyzer::UNDEFINED, headPredicate);
    term_rule->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::TERMINAL,
                        LexicalAnalyzer::COLON_DASH, nullptr);
    term_rule->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::GRAMMAR,
                        LexicalAnalyzer::UNDEFINED, predicate);
    term_rule->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::GRAMMAR,
                        LexicalAnalyzer::UNDEFINED, predicateList);
    term_rule->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::TERMINAL,
                        LexicalAnalyzer::PERIOD, nullptr);
    rule->addTermToGrammar(term_rule);

    // define terms of ruleList
    auto term_ruleList = Grammar<LexicalAnalyzer::TOKEN>::createTerm();
    term_ruleList->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::GRAMMAR,
                            LexicalAnalyzer::UNDEFINED, rule);
    term_ruleList->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::GRAMMAR,
                            LexicalAnalyzer::UNDEFINED, ruleList);
    ruleList->addTermToGrammar(term_ruleList);
    ruleList->addLambdaTerm();
//    ruleList->addTermToGrammar(term_Lambda);

    // define terms for head predicate
    auto term_headPredicate = Grammar<LexicalAnalyzer::TOKEN>::createTerm();
    term_headPredicate->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::TERMINAL,
                                 LexicalAnalyzer::ID, nullptr);
    term_headPredicate->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::TERMINAL,
                                 LexicalAnalyzer::LEFT_PARAM, nullptr);
    term_headPredicate->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::TERMINAL,
                                 LexicalAnalyzer::ID, nullptr);
    term_headPredicate->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::GRAMMAR,
                                 LexicalAnalyzer::UNDEFINED, idList);
    term_headPredicate->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::TERMINAL,
                                 LexicalAnalyzer::RIGHT_PARAM, nullptr);
    headPredicate->addTermToGrammar(term_headPredicate);

    // define terms for predicate
    auto term_predicate = Grammar<LexicalAnalyzer::TOKEN>::createTerm();
    term_predicate->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::TERMINAL,
                             LexicalAnalyzer::ID, nullptr);
    term_predicate->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::TERMINAL,
                             LexicalAnalyzer::LEFT_PARAM, nullptr);
    term_predicate->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::GRAMMAR,
                             LexicalAnalyzer::UNDEFINED, parameter);
    term_predicate->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::GRAMMAR,
                             LexicalAnalyzer::UNDEFINED, parameterList);
    term_predicate->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::TERMINAL,
                             LexicalAnalyzer::RIGHT_PARAM, nullptr);
    predicate->addTermToGrammar(term_predicate);

    // define terms for predicateList
    auto term_predicateList = Grammar<LexicalAnalyzer::TOKEN>::createTerm();
    term_predicateList->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::TERMINAL,
                                 LexicalAnalyzer::COMMA, nullptr);
    term_predicateList->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::GRAMMAR,
                                 LexicalAnalyzer::UNDEFINED, predicate);
    term_predicateList->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::GRAMMAR,
                                 LexicalAnalyzer::UNDEFINED, predicateList);
    predicateList->addTermToGrammar(term_predicateList);
    predicateList->addLambdaTerm();
//    predicateList->addTermToGrammar(term_Lambda);

    // define terms for parameter
    auto term_parameter_string = Grammar<LexicalAnalyzer::TOKEN>::createTerm();
    term_parameter_string->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::TERMINAL,
                                    LexicalAnalyzer::STRING, nullptr);
    auto term_parameter_id = Grammar<LexicalAnalyzer::TOKEN>::createTerm();
    term_parameter_id->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::TERMINAL,
                                LexicalAnalyzer::ID, nullptr);
    auto term_parameter_expression = Grammar<LexicalAnalyzer::TOKEN>::createTerm();
    term_parameter_expression->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::GRAMMAR,
                                        LexicalAnalyzer::UNDEFINED, expression);
    parameter->addTermToGrammar(term_parameter_string);
    parameter->addTermToGrammar(term_parameter_id);
    parameter->addTermToGrammar(term_parameter_expression);

    // define terms of parameterList
    auto term_parameterList = Grammar<LexicalAnalyzer::TOKEN>::createTerm();
    term_parameterList->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::TERMINAL,
                                 LexicalAnalyzer::COMMA, nullptr);
    term_parameterList->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::GRAMMAR,
                                 LexicalAnalyzer::UNDEFINED, parameter);
    term_parameterList->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::GRAMMAR,
                                 LexicalAnalyzer::UNDEFINED, parameterList);
    parameterList->addTermToGrammar(term_parameterList);
    parameterList->addLambdaTerm();
//    parameterList->addTermToGrammar(term_Lambda);

    // define terms of expression
    auto term_expression = Grammar<LexicalAnalyzer::TOKEN>::createTerm();
    term_expression->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::TERMINAL,
                              LexicalAnalyzer::LEFT_PARAM, nullptr);
    term_expression->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::GRAMMAR,
                              LexicalAnalyzer::UNDEFINED, parameter);
    term_expression->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::GRAMMAR,
                              LexicalAnalyzer::UNDEFINED, operatorG);
    term_expression->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::GRAMMAR,
                              LexicalAnalyzer::UNDEFINED, parameter);
    term_expression->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::TERMINAL,
                              LexicalAnalyzer::RIGHT_PARAM, nullptr);
    expression->addTermToGrammar(term_expression);

    // define operatorG terms
    auto term_operator_add = Grammar<LexicalAnalyzer::TOKEN>::createTerm();
    auto term_operator_mult = Grammar<LexicalAnalyzer::TOKEN>::createTerm();
    term_operator_add->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::TERMINAL,
                                LexicalAnalyzer::ADD, nullptr);
    term_operator_mult->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::TERMINAL,
                                 LexicalAnalyzer::MULTIPLY, nullptr);
    operatorG->addTermToGrammar(term_operator_add);
    operatorG->addTermToGrammar(term_operator_mult);

    // define terms of query
    auto term_query = Grammar<LexicalAnalyzer::TOKEN>::createTerm();
    term_query->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::GRAMMAR,
                         LexicalAnalyzer::UNDEFINED, predicate);
    term_query->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::TERMINAL,
                         LexicalAnalyzer::Q_MARK, nullptr);
    query->addTermToGrammar(term_query);

    // define terms of queryList
    auto term_queryList = Grammar<LexicalAnalyzer::TOKEN>::createTerm();
    term_queryList->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::GRAMMAR,
                             LexicalAnalyzer::UNDEFINED, query);
    term_queryList->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::GRAMMAR,
                             LexicalAnalyzer::UNDEFINED, queryList);
    queryList->addTermToGrammar(term_queryList);
    queryList->addLambdaTerm();
//    queryList->addTermToGrammar(term_Lambda);

    //define terms of stringlist
    auto term_stringList = Grammar<LexicalAnalyzer::TOKEN>::createTerm();
    term_stringList->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::TERMINAL,
                              LexicalAnalyzer::COMMA, nullptr);
    term_stringList->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::TERMINAL,
                              LexicalAnalyzer::STRING, nullptr);
    term_stringList->addEntry(Grammar<LexicalAnalyzer::TOKEN>::Term<LexicalAnalyzer::TOKEN>::GRAMMAR,
                              LexicalAnalyzer::UNDEFINED, stringList);
    stringList->addTermToGrammar(term_stringList);
    stringList->addLambdaTerm();
}

DataParser::~DataParser() = default;

void DataParser::checkValidity() {

    std::vector<LexicalAnalyzer::token_struct> listOfTokens = lexicalAnalyzer->getTokenList();
    std::vector<LexicalAnalyzer::TOKEN> tokens;

    tokens.reserve(listOfTokens.size()); // Just make sure that we minimize vector allocation time
    for (auto &p : listOfTokens) {
        tokens.push_back(p.token);
    }

    tokens.push_back(LexicalAnalyzer::EOF_TOKEN);

    int index = 0;
    try {
        datalogGrammar->proccessList(tokens, index);
        if (index < tokens.size() && tokens.at(index) != LexicalAnalyzer::EOF_TOKEN)
            throw GrammarException(index, "", "");
        std::cout << "Successful!" << std::endl;
    } catch (std::string &e) {
        std::cout << "Failed: " << e << index << std::endl;
    } catch (GrammarException &grammarException) {
        std::cout << "Failure!" << std::endl;
        std::string token = LexicalAnalyzer::enumToString(
                listOfTokens.at(static_cast<unsigned long>(grammarException.getIndex())).token);
        int lineNumber = listOfTokens.at(static_cast<unsigned long>(grammarException.getIndex())).lineNumber;
        std::string tokenStr = listOfTokens.at(static_cast<unsigned long>(grammarException.getIndex())).tokenStr;
        std::cout << "(" << token << ", " << lineNumber << ", \"" << tokenStr << "\")" << std::endl;
    }

}

// calls the grammars clean function before deleting the pointers
void DataParser::clean() {
    for (auto &grammar : listOfGrammars) {
        grammar->clean();
        delete grammar;
    }
}
