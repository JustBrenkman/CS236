//
// Created by bbrenk on 10/15/18.
//

#include "Parameter.h"
#include "Expression.h"
#include "Id.h"
#include "DLString.h"

bool Parameter::inInFirstOf(std::vector<LexicalAnalyzer::token_struct> &list, LexicalAnalyzer::TOKEN tokenType,
                            unsigned int &index) {

    switch (list.at(index).token) {
        case LexicalAnalyzer::ID:
            break;
        case LexicalAnalyzer::STRING:
            break;
        case LexicalAnalyzer::LEFT_PARAM:
            break;
        default:
            return false;
    }

    return true;
}

Parameter *Parameter::createParameter(std::vector<LexicalAnalyzer::token_struct> &list, unsigned int &index) {

    Parameter *parameter = nullptr;

    switch (list.at(index).token) {
        case LexicalAnalyzer::ID:
            parameter = new Id(list, index);
            break;
        case LexicalAnalyzer::STRING:
            parameter = new DLString(list, index);
            break;
        case LexicalAnalyzer::LEFT_PARAM:
            parameter = new Expression(list, index);
            break;
        default:
            throw GrammarException(index, "", "");
    }

    return parameter;
}

std::string Parameter::toString() const { return std::string(); }

void Parameter::clean() {}

Parameter::~Parameter() = default;

Parameter::Parameter() = default;
