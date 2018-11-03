//
// Created by bbrenk on 10/12/18.
//

#ifndef LAB2_GRAMMAREXCEPTION_H
#define LAB2_GRAMMAREXCEPTION_H


#include <string>

class GrammarException {

private:
    int index;
    std::string expectedToken, tokenReceived;
public:
    GrammarException(int index, std::string expectedToken, std::string tokenReceived);

    ~GrammarException();

    int getIndex();

    std::string getExpectedToken();

    std::string getTokenReceived();
};


#endif //LAB2_GRAMMAREXCEPTION_H
