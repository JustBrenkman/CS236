#include <utility>

//
// Created by bbrenk on 10/12/18.
//

#include "GrammarException.h"

GrammarException::GrammarException(int index, std::string expectedToken, std::string tokenReceived) {
    this->index = index;
    this->expectedToken = std::move(expectedToken);
    this->tokenReceived = std::move(tokenReceived);
}

std::string GrammarException::getExpectedToken() {
    return expectedToken;
}

int GrammarException::getIndex() {
    return index;
}

std::string GrammarException::getTokenReceived() {
    return tokenReceived;
}

GrammarException::~GrammarException() = default;
