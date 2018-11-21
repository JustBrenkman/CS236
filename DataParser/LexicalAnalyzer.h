#ifndef LEXICAL_ANALYZER_H
#define LEXICAL_ANALYZER_H

#include <iostream>
#include <string>
#include "FiniteStateMachine.h"

/*******************************************************************************************

File: Lyxical Analyzer
Author: Ben Brenkman
version: 1.0

Purpose: This is the lexical analyzer, it used a Finite State Machine to generate a list
		 of tokens. The tokens are defined in the enum below.

		 Inputs: {',', '.', '?', '(', ')', ':', ':-', '*', '+', 'Schemes', 'Facts',
				  'Rules', 'Queries', '8asdagsd', ''a string'', '# a comment'}

		 Outputs: {'COMMA', 'PERIOD', 'Q_MARK', 'LEFT_PAREN', 'RIGHT_PAREN',
		           'COLON', 'COLON_DASH', 'MULTIPLY', 'ADD', 'SCHEMES', 'FACTS', 'RULES',
				   'QUERIES', 'ID', ''STRING'', 'COMMENT'}

*******************************************************************************************/

class LexicalAnalyzer {
public:
    enum TOKEN { COMMA, PERIOD, Q_MARK, LEFT_PARAM, RIGHT_PARAM,
        COLON, COLON_DASH, MULTIPLY, ADD, SCHEMES, FACTS,
        RULES, QUERIES, ID, STRING, COMMENT, WHITESPACE,
        UNDEFINED, EOF_TOKEN, NULL_TOKEN };

    //
    const std::string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const std::string digits = "0123456789";
    const std::string alphabetDigits = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int lineNumber = 1; // Line number
    int tokenLineNumber = 1;
    std::string tokenSegment; // This is the output with every token

    // This function will proccess the input stream and feed it into the fsm
    void proccessChar(char c) {
        if (c == '\n')
            lineNumber++;
        // Proccess the char
        fsm->proccessEvent(c, this);
        // If there was an undefined trigger throw it means we need to reproccess it
        // This will make sure we don't skip the next char and flush the fsm
        // This can be replaced by turning the fsm into a finite state autonoma
        if (flagReproccess) {
            flagReproccess = false;
            fsm->switchStates("start"); // switch the the start state and reproccess
            fsm->proccessEvent(c, this);
        }
    }

    // Proccess the input of an entire string
    void proccessInput(std::string input) {

        for (unsigned int i = 0; i < input.length(); i++) {
            // Go through every char in the string and proccess it
            proccessChar(input.at(i));
        }

        // Proccess an end of file
        proccessChar('\0');

        // Add the final token, which is an EOF
        // TODO absorb token into fsm
        if (fsm->isCurrentStateAccepting()) {
            if (previous != WHITESPACE) {
                addTokenToList();
            }
        }
    }

    // This is the callback from the fsm when the fsm encouters a switch
    void fsmCallback(TOKEN t) {
//        std::cout << "Current: " << enumToString(t) << ", Previous: " << enumToString(previous) <<  std::endl;
        //std::cout << enumToString(t) <<  std::endl;
        if (t == UNDEFINED) {
            if (fsm->isCurrentStateAccepting()) {
                if (previous != WHITESPACE) {
                    //std::cout << enumToString(previous) << std::endl;
                    addTokenToList();
                }
            } else {
                addTokenToList();
            }

            if (previous != UNDEFINED) {
                flagReproccess = true; //flag to reproccess char
            }
        }
        tokenLineNumber = lineNumber; // updates the line number that is saved only after submitting a token
        previous = t;
    }

    // Adds a token and some information to a list
    void addTokenToList() {
        if (tokenSegment == "::")
            tokenSegment = ":";

        token_struct t_struct;
        t_struct.token = previous;
        t_struct.tokenStr = tokenSegment;
        t_struct.lineNumber = tokenLineNumber;
        listOfTokens.push_back(t_struct);
        tokenSegment = std::string();

        //Initialize the iterator
        curretntItr = listOfTokens.begin();
    }

    // These are the state definition functions, this controls the logic of the initial state
    void initialStateDeterminant(FiniteStateMachine<char, TOKEN, LexicalAnalyzer>* fsm, char c) {
        //std::cout << "Start proccess" << std::endl;
        switch (c)
        {
            case ',':
                tokenSegment.append(std::string(1, c));
                fsm->triggerStateChangeEvent(COMMA, this);
                fsm->switchStates("comma");
                break;
            case '.':
                tokenSegment.append(std::string(1, c));
                fsm->triggerStateChangeEvent(PERIOD, this);
                fsm->switchStates("period");
                break;
            case '?':
                tokenSegment.append(std::string(1, c));
                fsm->triggerStateChangeEvent(Q_MARK, this);
                fsm->switchStates("q-mark");
                break;
            case '(':
                tokenSegment.append(std::string(1, c));
                fsm->triggerStateChangeEvent(LEFT_PARAM, this);
                fsm->switchStates("left-paren");
                break;
            case ')':
                tokenSegment.append(std::string(1, c));
                fsm->triggerStateChangeEvent(RIGHT_PARAM, this);
                fsm->switchStates("right-paren");
                break;
            case ':':
                tokenSegment.append(std::string(1, c));
                fsm->triggerStateChangeEvent(COLON, this);
                fsm->switchStates("colon");
                break;
            case '*':
                tokenSegment.append(std::string(1, c));
                fsm->triggerStateChangeEvent(MULTIPLY, this);
                fsm->switchStates("multiply");
                break;
            case '+':
                tokenSegment.append(std::string(1, c));
                fsm->triggerStateChangeEvent(ADD, this);
                fsm->switchStates("add");
                break;
            case 'S':
                tokenSegment.append(std::string(1, c));
                fsm->triggerStateChangeEvent(ID, this);
                fsm->switchStates("scheme-S");
                break;
            case 'F':
                tokenSegment.append(std::string(1, c));
                fsm->triggerStateChangeEvent(ID, this);
                fsm->switchStates("facts-F");
                break;
            case 'R':
                tokenSegment.append(std::string(1, c));
                fsm->triggerStateChangeEvent(ID, this);
                fsm->switchStates("rules-R");
                break;
            case 'Q':
                tokenSegment.append(std::string(1, c));
                fsm->triggerStateChangeEvent(ID, this);
                fsm->switchStates("queries-Q");
                break;
            case '\'':
                tokenSegment.append(std::string(1, c));
                fsm->triggerStateChangeEvent(STRING, this);
                fsm->switchStates("string-begin");
                break;
            case '#':
                tokenSegment.append(std::string(1, c));
                fsm->triggerStateChangeEvent(COMMENT, this);
                fsm->switchStates("comment");
                break;
            case ' ':
                fsm->triggerStateChangeEvent(WHITESPACE, this);
                fsm->switchStates("whitespace");
                break;
            case '\n':
                break;
            case '\0':
                fsm->triggerStateChangeEvent(EOF_TOKEN, this);
                break;
            default:
                if (alphabet.find(c) != std::string::npos) {
                    tokenSegment.append(std::string(1, c));
                    fsm->triggerStateChangeEvent(ID, this);
                    fsm->switchStates("id");
                }
                else {
                    tokenSegment.append(std::string(1, c));
                    fsm->triggerStateChangeEvent(UNDEFINED, this);
                }
                break;
        }
    }


    // Comma state
    void comma(FiniteStateMachine<char, TOKEN, LexicalAnalyzer>* fsm, char c) {
        fsm->triggerStateChangeEvent(UNDEFINED, this);
    }

    // Question mark state
    void qmark(FiniteStateMachine<char, TOKEN, LexicalAnalyzer>* fsm, char c) {
        fsm->triggerStateChangeEvent(UNDEFINED, this);
    }

    // Left parenthese state
    void leftparen(FiniteStateMachine<char, TOKEN, LexicalAnalyzer>* fsm, char c) {
        fsm->triggerStateChangeEvent(UNDEFINED, this);
    }

    // right parenthese state
    void rightparen(FiniteStateMachine<char, TOKEN, LexicalAnalyzer>* fsm, char c) {
        fsm->triggerStateChangeEvent(UNDEFINED, this);
    }

    // Colon state logic
    void colon(FiniteStateMachine<char, TOKEN, LexicalAnalyzer>* fsm, char c) {
        switch (c)
        {
            case '-':
                tokenSegment.append(std::string(1, c));
                fsm->switchStates("colon-dash");
                fsm->triggerStateChangeEvent(COLON_DASH, this);
                break;
            default:
                fsm->triggerStateChangeEvent(UNDEFINED, this);
                break;
        }
    }

    // Colon dash state logic
    void colondash(FiniteStateMachine<char, TOKEN, LexicalAnalyzer>* fsm, char c) {
        fsm->triggerStateChangeEvent(UNDEFINED, this);
    }

    // Multiply state
    void multiply(FiniteStateMachine<char, TOKEN, LexicalAnalyzer>* fsm, char c) {
        fsm->triggerStateChangeEvent(UNDEFINED, this);
    }

    // Add state
    void add(FiniteStateMachine<char, TOKEN, LexicalAnalyzer>* fsm, char c) {
        fsm->triggerStateChangeEvent(UNDEFINED, this);
    }

    /*******************************************************************************************************************************
                                                            Scheme states
    *******************************************************************************************************************************/
    // First in the set of Scheme states
    void schemeS(FiniteStateMachine<char, TOKEN, LexicalAnalyzer>* fsm, char c) {
        switch (c)
        {
            case 'c':
                tokenSegment.append(std::string(1, c));
                fsm->switchStates("scheme-c");
                break;
            default:
                if (alphabet.find(c) != std::string::npos) {
                    tokenSegment.append(std::string(1, c));
                    fsm->triggerStateChangeEvent(ID, this);
                    fsm->switchStates("id");
                }
                else {
                    fsm->triggerStateChangeEvent(UNDEFINED, this);
                }
                break;
        }
    }
    // Second in the set of Scheme states
    void schemec(FiniteStateMachine<char, TOKEN, LexicalAnalyzer>* fsm, char c) {
        switch (c)
        {
            case 'h':
                tokenSegment.append(std::string(1, c));
                fsm->switchStates("scheme-h");
                break;
            default:
                if (alphabet.find(c) != std::string::npos) {
                    tokenSegment.append(std::string(1, c));
                    fsm->triggerStateChangeEvent(ID, this);
                    fsm->switchStates("id");
                }
                else {
                    fsm->triggerStateChangeEvent(UNDEFINED, this);
                }
                break;
        }
    }

    // Third in the set of Scheme states
    void schemeh(FiniteStateMachine<char, TOKEN, LexicalAnalyzer>* fsm, char c) {
        switch (c)
        {
            case 'e':
                tokenSegment.append(std::string(1, c));
                fsm->switchStates("scheme-e");
                break;
            default:
                if (alphabet.find(c) != std::string::npos) {
                    tokenSegment.append(std::string(1, c));
                    fsm->triggerStateChangeEvent(ID, this);
                    fsm->switchStates("id");
                }
                else {
                    fsm->triggerStateChangeEvent(UNDEFINED, this);
                }
                break;
        }
    }

    // Fourth in the set of Scheme states
    void schemee(FiniteStateMachine<char, TOKEN, LexicalAnalyzer>* fsm, char c) {
        switch (c)
        {
            case 'm':
                tokenSegment.append(std::string(1, c));
                fsm->switchStates("scheme-m");
                break;
            default:
                if (alphabet.find(c) != std::string::npos) {
                    tokenSegment.append(std::string(1, c));
                    fsm->triggerStateChangeEvent(ID, this);
                    fsm->switchStates("id");
                }
                else {
                    fsm->triggerStateChangeEvent(UNDEFINED, this);
                }
                break;
        }
    }

    // Fifth in the set of Scheme states
    void schemem(FiniteStateMachine<char, TOKEN, LexicalAnalyzer>* fsm, char c) {
        switch (c)
        {
            case 'e':
                tokenSegment.append(std::string(1, c));
                fsm->switchStates("scheme-final-e");
                break;
            default:
                if (alphabet.find(c) != std::string::npos) {
                    tokenSegment.append(std::string(1, c));
                    fsm->triggerStateChangeEvent(ID, this);
                    fsm->switchStates("id");
                }
                else {
                    fsm->triggerStateChangeEvent(UNDEFINED, this);
                }
                break;
        }
    }

    // Sixth in the set of Scheme states
    void schemeFinale(FiniteStateMachine<char, TOKEN, LexicalAnalyzer>* fsm, char c) {
        switch (c)
        {
            case 's':
                tokenSegment.append(std::string(1, c));
                fsm->triggerStateChangeEvent(SCHEMES, this);
                fsm->switchStates("scheme-s");
                break;
            default:
                if (alphabet.find(c) != std::string::npos) {
                    tokenSegment.append(std::string(1, c));
                    fsm->triggerStateChangeEvent(ID, this);
                    fsm->switchStates("id");
                }
                else {
                    fsm->triggerStateChangeEvent(UNDEFINED, this);
                }
                break;
        }
    }

    // Last in the set of Scheme states
    void schemes(FiniteStateMachine<char, TOKEN, LexicalAnalyzer>* fsm, char c) {
        if (alphabet.find(c) != std::string::npos) {
            tokenSegment.append(std::string(1, c));
            fsm->triggerStateChangeEvent(ID, this);
            fsm->switchStates("id");
        }
        else {
            fsm->triggerStateChangeEvent(UNDEFINED, this);
        }
    }

    /*******************************************************************************************************************************
                                                        Facts states
    *******************************************************************************************************************************/
    // First in the set of Facts states
    void factsF(FiniteStateMachine<char, TOKEN, LexicalAnalyzer>* fsm, char c) {
        switch (c)
        {
            case 'a':
                tokenSegment.append(std::string(1, c));
                fsm->switchStates("facts-a");
                break;
            default:
                if (alphabet.find(c) != std::string::npos) {
                    tokenSegment.append(std::string(1, c));
                    fsm->triggerStateChangeEvent(ID, this);
                    fsm->switchStates("id");
                }
                else {
                    fsm->triggerStateChangeEvent(UNDEFINED, this);
                }
                break;
        }
    }

    // Second in the set of Facts states
    void factsa(FiniteStateMachine<char, TOKEN, LexicalAnalyzer>* fsm, char c) {
        switch (c)
        {
            case 'c':
                tokenSegment.append(std::string(1, c));
                fsm->switchStates("facts-c");
                break;
            default:
                if (alphabet.find(c) != std::string::npos) {
                    tokenSegment.append(std::string(1, c));
                    fsm->triggerStateChangeEvent(ID, this);
                    fsm->switchStates("id");
                }
                else {
                    fsm->triggerStateChangeEvent(UNDEFINED, this);
                }
                break;
        }
    }

    // Third in the set of Facts states
    void factsc(FiniteStateMachine<char, TOKEN, LexicalAnalyzer>* fsm, char c) {
        switch (c)
        {
            case 't':
                tokenSegment.append(std::string(1, c));
                fsm->switchStates("facts-t");
                break;
            default:
                if (alphabet.find(c) != std::string::npos) {
                    tokenSegment.append(std::string(1, c));
                    fsm->triggerStateChangeEvent(ID, this);
                    fsm->switchStates("id");
                }
                else {
                    fsm->triggerStateChangeEvent(UNDEFINED, this);
                }
                break;
        }
    }

    // Fourth in the set of Facts states
    void factst(FiniteStateMachine<char, TOKEN, LexicalAnalyzer>* fsm, char c) {
        switch (c)
        {
            case 's':
                tokenSegment.append(std::string(1, c));
                fsm->triggerStateChangeEvent(FACTS, this);
                fsm->switchStates("facts-s");
                break;
            default:
                if (alphabet.find(c) != std::string::npos) {
                    tokenSegment.append(std::string(1, c));
                    fsm->triggerStateChangeEvent(ID, this);
                    fsm->switchStates("id");
                }
                else {
                    fsm->triggerStateChangeEvent(UNDEFINED, this);
                }
                break;
        }
    }

    // Last in the set of Facts states
    void factss(FiniteStateMachine<char, TOKEN, LexicalAnalyzer>* fsm, char c) {
        if (alphabet.find(c) != std::string::npos) {
            tokenSegment.append(std::string(1, c));
            fsm->triggerStateChangeEvent(ID, this);
            fsm->switchStates("id");
        }
        else {
            fsm->triggerStateChangeEvent(UNDEFINED, this);
        }
    }

    /*******************************************************************************************************************************
                                                            Rules states
    *******************************************************************************************************************************/
    // First in the set of Rules states
    void rulesR(FiniteStateMachine<char, TOKEN, LexicalAnalyzer>* fsm, char c) {
        switch (c)
        {
            case 'u':
                tokenSegment.append(std::string(1, c));
                fsm->switchStates("rules-u");
                break;
            default:
                if (alphabet.find(c) != std::string::npos) {
                    tokenSegment.append(std::string(1, c));
                    fsm->triggerStateChangeEvent(ID, this);
                    fsm->switchStates("id");
                }
                else {
                    fsm->triggerStateChangeEvent(UNDEFINED, this);
                }
                break;
        }
    }

    // Second in the set of Rules states
    void rulesu(FiniteStateMachine<char, TOKEN, LexicalAnalyzer>* fsm, char c) {
        switch (c)
        {
            case 'l':
                tokenSegment.append(std::string(1, c));
                fsm->switchStates("rules-l");
                break;
            default:
                if (alphabet.find(c) != std::string::npos) {
                    tokenSegment.append(std::string(1, c));
                    fsm->triggerStateChangeEvent(ID, this);
                    fsm->switchStates("id");
                }
                else {
                    fsm->triggerStateChangeEvent(UNDEFINED, this);
                }
                break;
        }
    }

    // Third in the set of Rules states
    void rulesl(FiniteStateMachine<char, TOKEN, LexicalAnalyzer>* fsm, char c) {
        switch (c)
        {
            case 'e':
                tokenSegment.append(std::string(1, c));
                fsm->switchStates("rules-e");
                break;
            default:
                if (alphabet.find(c) != std::string::npos) {
                    tokenSegment.append(std::string(1, c));
                    fsm->triggerStateChangeEvent(ID, this);
                    fsm->switchStates("id");
                }
                else {
                    fsm->triggerStateChangeEvent(UNDEFINED, this);
                }
                break;
        }
    }

    // Fourth in the set of Rules states
    void rulese(FiniteStateMachine<char, TOKEN, LexicalAnalyzer>* fsm, char c) {
        switch (c)
        {
            case 's':
                tokenSegment.append(std::string(1, c));
                fsm->triggerStateChangeEvent(RULES, this);
                fsm->switchStates("rules-s");
                break;
            default:
                if (alphabet.find(c) != std::string::npos) {
                    tokenSegment.append(std::string(1, c));
                    fsm->triggerStateChangeEvent(ID, this);
                    fsm->switchStates("id");
                }
                else {
                    fsm->triggerStateChangeEvent(UNDEFINED, this);
                }
                break;
        }
    }

    // Last in the set of Rules states
    void ruless(FiniteStateMachine<char, TOKEN, LexicalAnalyzer>* fsm, char c) {
        if (alphabet.find(c) != std::string::npos) {
            tokenSegment.append(std::string(1, c));
            fsm->triggerStateChangeEvent(ID, this);
            fsm->switchStates("id");
        }
        else {
            fsm->triggerStateChangeEvent(UNDEFINED, this);
        }
    }

    /*******************************************************************************************************************************
                                                                Queries states
    *******************************************************************************************************************************/

    // First in the set of Queries states
    void queriesQ(FiniteStateMachine<char, TOKEN, LexicalAnalyzer>* fsm, char c) {
        switch (c)
        {
            case 'u':
                tokenSegment.append(std::string(1, c));
                fsm->switchStates("queries-u");
                break;
            default:
                if (alphabet.find(c) != std::string::npos) {
                    tokenSegment.append(std::string(1, c));
                    //fsm->triggerStateChangeEvent(ID, this);
                    fsm->switchStates("id");
                }
                else {
                    fsm->triggerStateChangeEvent(UNDEFINED, this);
                }
                break;
        }
    }

    // Second in the set of Queries states
    void queriesu(FiniteStateMachine<char, TOKEN, LexicalAnalyzer>* fsm, char c) {
        switch (c)
        {
            case 'e':
                tokenSegment.append(std::string(1, c));
                fsm->switchStates("queries-e");
                break;
            default:
                if (alphabet.find(c) != std::string::npos) {
                    tokenSegment.append(std::string(1, c));
                    //fsm->triggerStateChangeEvent(ID, this);
                    fsm->switchStates("id");
                }
                else {
                    fsm->triggerStateChangeEvent(UNDEFINED, this);
                }
                break;
        }
    }

    // Third in the set of Queries states
    void queriese(FiniteStateMachine<char, TOKEN, LexicalAnalyzer>* fsm, char c) {
        switch (c)
        {
            case 'r':
                tokenSegment.append(std::string(1, c));
                fsm->switchStates("queries-r");
                break;
            default:
                if (alphabet.find(c) != std::string::npos) {
                    tokenSegment.append(std::string(1, c));
                    //fsm->triggerStateChangeEvent(ID, this);
                    fsm->switchStates("id");
                }
                else {
                    fsm->triggerStateChangeEvent(UNDEFINED, this);
                }
                break;
        }
    }

    // Fourth in the set of Queries states
    void queriesr(FiniteStateMachine<char, TOKEN, LexicalAnalyzer>* fsm, char c) {
        switch (c)
        {
            case 'i':
                tokenSegment.append(std::string(1, c));
                fsm->switchStates("queries-i");
                break;
            default:
                if (alphabet.find(c) != std::string::npos) {
                    tokenSegment.append(std::string(1, c));
                    //fsm->triggerStateChangeEvent(ID, this);
                    fsm->switchStates("id");
                }
                else {
                    fsm->triggerStateChangeEvent(UNDEFINED, this);
                }
                break;
        }
    }

    // Fifth in the set of Queries states
    void queriesi(FiniteStateMachine<char, TOKEN, LexicalAnalyzer>* fsm, char c) {
        switch (c)
        {
            case 'e':
                tokenSegment.append(std::string(1, c));
                fsm->switchStates("queries-e2");
                break;
            default:
                if (alphabet.find(c) != std::string::npos) {
                    tokenSegment.append(std::string(1, c));
                    //fsm->triggerStateChangeEvent(ID, this);
                    fsm->switchStates("id");
                }
                else {
                    fsm->triggerStateChangeEvent(UNDEFINED, this);
                }
                break;
        }
    }

    // Sixth in the set of Queries states
    void queriese2(FiniteStateMachine<char, TOKEN, LexicalAnalyzer>* fsm, char c) {
        switch (c)
        {
            case 's':
                tokenSegment.append(std::string(1, c));
                previous = QUERIES;
                fsm->triggerStateChangeEvent(QUERIES, this);
                //std::cout << "Quereies 709" << std::endl;
                fsm->switchStates("queries-s");
                break;
            default:
                if (alphabet.find(c) != std::string::npos) {
                    tokenSegment.append(std::string(1, c));
                    //fsm->triggerStateChangeEvent(ID, this);
                    fsm->switchStates("id");
                }
                else {
                    fsm->triggerStateChangeEvent(UNDEFINED, this);
                }
                break;
        }
    }

    // Last in the set of Queries states
    void queriess(FiniteStateMachine<char, TOKEN, LexicalAnalyzer>* fsm, char c) {
        if (alphabet.find(c) != std::string::npos) {
            tokenSegment.append(std::string(1, c));
            fsm->triggerStateChangeEvent(ID, this);
            fsm->switchStates("id");
        }
        else {
            fsm->triggerStateChangeEvent(UNDEFINED, this);
        }
    }

    // ID
    void id(FiniteStateMachine<char, TOKEN, LexicalAnalyzer>* fsm, char c) {
        if (alphabetDigits.find(c) == std::string::npos) {
            fsm->triggerStateChangeEvent(UNDEFINED, this);
        }
        else {
            tokenSegment.append(std::string(1, c));
        }
    }

    // String
    void stringBegin(FiniteStateMachine<char, TOKEN, LexicalAnalyzer>* fsm, char c) {
        switch (c)
        {
            case'\'':
                tokenSegment.append(std::string(1, c));
                fsm->switchStates("string-end");
                break;
            case '\0':
                previous = UNDEFINED;
                fsm->triggerStateChangeEvent(UNDEFINED, this);
                break;
            default:
                tokenSegment.append(std::string(1, c));
                break;
        }
    }

    void stringEnd(FiniteStateMachine<char, TOKEN, LexicalAnalyzer>* fsm, char c) {
        switch (c)
        {
            case '\'':
                tokenSegment.append(std::string(1, c));
                fsm->switchStates("string-begin");
                break;
            default:
                //previous = UNDEFINED;
                fsm->triggerStateChangeEvent(UNDEFINED, this);
                break;
        }
    }

    /*******************************************************************************************************************************
                                                        Comment states
    *******************************************************************************************************************************/

    // First comment state
    void comment(FiniteStateMachine<char, TOKEN, LexicalAnalyzer>* fsm, char c) {
        switch (c)
        {
            case '|':
                tokenSegment.append(std::string(1, c));
                fsm->switchStates("comment-content-multi");
                break;
            default:
                tokenSegment.append(std::string(1, c));
                //fsm->triggerStateChangeEvent(COMMENT, this);
                fsm->switchStates("comment-content-single");
                break;
        }
    }

    // Second comment state
    void commentContentSingle(FiniteStateMachine<char, TOKEN, LexicalAnalyzer>* fsm, char c) {
        switch (c)
        {
            case '\n':
                fsm->switchStates("comment-end");
                break;
            default:
                tokenSegment.append(std::string(1, c));
                // Do nothing
                break;
        }
    }

    // Third comment state
    void commentMulti(FiniteStateMachine<char, TOKEN, LexicalAnalyzer>* fsm, char c) {
        tokenSegment.append(std::string(1, c));
        fsm->switchStates("comment-content-multi");
    }

    // Fourth comment state
    void commentContentMulti(FiniteStateMachine<char, TOKEN, LexicalAnalyzer>* fsm, char c) {
        switch (c)
        {
            case '|':
                tokenSegment.append(std::string(1, c));
                fsm->switchStates("comment-multi-end");
                break;
            case '\0':
                previous = UNDEFINED;
                fsm->triggerStateChangeEvent(UNDEFINED, this);
                break;
            default:
                tokenSegment.append(std::string(1, c));
                break;
        }
    }

    // Fifth comment state
    void commentMultiEnd(FiniteStateMachine<char, TOKEN, LexicalAnalyzer>* fsm, char c) {
        switch (c)
        {
            case '#':
                tokenSegment.append(std::string(1, c));
                fsm->switchStates("comment-end");
                break;
            case '\0':
                previous = UNDEFINED;
                fsm->triggerStateChangeEvent(UNDEFINED, this);
                break;
            default:
                tokenSegment.append(std::string(1, c));
                fsm->switchStates("comment-content-multi");
                break;
        }
    }

    // Last comment state -- These are empty end states, they are just to signify that this is it
    void commentContentEnd(FiniteStateMachine<char, TOKEN, LexicalAnalyzer>* fsm, char c) {
        fsm->triggerStateChangeEvent(UNDEFINED, this);
    }

    // Whitespace
    void whitespace(FiniteStateMachine<char, TOKEN, LexicalAnalyzer>* fsm, char c) {
        fsm->triggerStateChangeEvent(UNDEFINED, this);
    }

    // Period
    void period(FiniteStateMachine<char, TOKEN, LexicalAnalyzer>* fsm, char c) {
        fsm->triggerStateChangeEvent(UNDEFINED, this);
    }

    // Converst the token to a string
    static std::string enumToString(int enumVal) {
        // Cool way to do it
        const std::string enumStrings[] = { "COMMA", "PERIOD", "Q_MARK", "LEFT_PAREN", "RIGHT_PAREN",
                                            "COLON", "COLON_DASH", "MULTIPLY", "ADD", "SCHEMES", "FACTS",
                                            "RULES", "QUERIES", "ID", "STRING", "COMMENT", "WHITESPACE",
                                            "UNDEFINED", "EOF", "NULL_TOKEN" };
        return enumStrings[enumVal];
    }

    // This is the token struct, it will store the data for each token
    struct token_struct {
        TOKEN token;
        std::string tokenStr;
        int lineNumber;
    };

    // Prints the Lexical Analyzer into a string
    std::string toString() {
        std::string str;

        for (auto tk : listOfTokens) {
            str.append("(");
            str.append(enumToString(tk.token));
            str.append(",\"");
            str.append(tk.tokenStr);
            str.append("\",");
            str.append(std::to_string(tk.lineNumber));
            str.append(")");
            str.append("\n");
        }

        str.append("(");
        str.append(enumToString(EOF_TOKEN));
        str.append(",\"");
        str.append("\",");
        str.append(std::to_string(lineNumber));
        str.append(")");
        str.append("\n");

        str.append("Total Tokens = ");
        str.append(std::to_string(listOfTokens.size() + 1));

        return str;
    }

    // Friend mehtod for generating printing the lexical analyzer
    friend std::ostream& operator<<(std::ostream& os, LexicalAnalyzer lex) {
//        os << "Printing the lexical analyzer..." << std::endl;
        os << lex.toString();
        return os;
    }

    TOKEN getCurrentToken();
    void advanceToken();
    bool isAtEnd();

private:
    FiniteStateMachine<char, TOKEN, LexicalAnalyzer>* fsm; // Finite State Machine used
    TOKEN previous = UNDEFINED; // used to proccess the fsm output
    bool flagReproccess = false; // reproccess flag
    std::vector<token_struct> listOfTokens; // List of tokens found in input
    std::vector<token_struct>::iterator curretntItr;
public:
    LexicalAnalyzer() {
        // Creates a new FiniteStateMachine
        fsm = new FiniteStateMachine<char, TOKEN, LexicalAnalyzer>(); // Create a new FSM
        // Initialize the finite state machine and add the state
        fsm->setCallbackFunction(&LexicalAnalyzer::fsmCallback);

        // Start state
        fsm->addState(fsm->createState(&LexicalAnalyzer::initialStateDeterminant, this, false), "start");

        // Single states
        fsm->addState(fsm->createState(&LexicalAnalyzer::comma, this, true), "comma");
        fsm->addState(fsm->createState(&LexicalAnalyzer::qmark, this, true), "q-mark");
        fsm->addState(fsm->createState(&LexicalAnalyzer::leftparen, this, true), "left-paren");
        fsm->addState(fsm->createState(&LexicalAnalyzer::rightparen, this, true), "right-paren");
        fsm->addState(fsm->createState(&LexicalAnalyzer::colon, this, true), "colon");
        fsm->addState(fsm->createState(&LexicalAnalyzer::colondash, this, true), "colon-dash");
        fsm->addState(fsm->createState(&LexicalAnalyzer::multiply, this, true), "multiply");
        fsm->addState(fsm->createState(&LexicalAnalyzer::add, this, true), "add");

        // Schemes states
        fsm->addState(fsm->createState(&LexicalAnalyzer::schemeS, this, true), "scheme-S");
        fsm->addState(fsm->createState(&LexicalAnalyzer::schemec, this, false), "scheme-c");
        fsm->addState(fsm->createState(&LexicalAnalyzer::schemeh, this, false), "scheme-h");
        fsm->addState(fsm->createState(&LexicalAnalyzer::schemee, this, false), "scheme-e");
        fsm->addState(fsm->createState(&LexicalAnalyzer::schemem, this, false), "scheme-m");
        fsm->addState(fsm->createState(&LexicalAnalyzer::schemeFinale, this, false), "scheme-final-e");
        fsm->addState(fsm->createState(&LexicalAnalyzer::schemes, this, true), "scheme-s");

        //Facts states
        fsm->addState(fsm->createState(&LexicalAnalyzer::factsF, this, true), "facts-F");
        fsm->addState(fsm->createState(&LexicalAnalyzer::factsa, this, false), "facts-a");
        fsm->addState(fsm->createState(&LexicalAnalyzer::factsc, this, false), "facts-c");
        fsm->addState(fsm->createState(&LexicalAnalyzer::factst, this, false), "facts-t");
        fsm->addState(fsm->createState(&LexicalAnalyzer::factss, this, true), "facts-s");


        //Rules states
        fsm->addState(fsm->createState(&LexicalAnalyzer::rulesR, this, true), "rules-R");
        fsm->addState(fsm->createState(&LexicalAnalyzer::rulesu, this, false), "rules-u");
        fsm->addState(fsm->createState(&LexicalAnalyzer::rulesl, this, false), "rules-l");
        fsm->addState(fsm->createState(&LexicalAnalyzer::rulese, this, false), "rules-e");
        fsm->addState(fsm->createState(&LexicalAnalyzer::ruless, this, true), "rules-s");

        //Queries states
        fsm->addState(fsm->createState(&LexicalAnalyzer::queriesQ, this, true), "queries-Q");
        fsm->addState(fsm->createState(&LexicalAnalyzer::queriesu, this, false), "queries-u");
        fsm->addState(fsm->createState(&LexicalAnalyzer::queriese, this, false), "queries-e");
        fsm->addState(fsm->createState(&LexicalAnalyzer::queriesr, this, false), "queries-r");
        fsm->addState(fsm->createState(&LexicalAnalyzer::queriesi, this, false), "queries-i");
        fsm->addState(fsm->createState(&LexicalAnalyzer::queriese2, this, false), "queries-e2");
        fsm->addState(fsm->createState(&LexicalAnalyzer::queriess, this, true), "queries-s");

        // ID state
        fsm->addState(fsm->createState(&LexicalAnalyzer::id, this, true), "id");

        // String states
        fsm->addState(fsm->createState(&LexicalAnalyzer::stringBegin, this, false), "string-begin");
        fsm->addState(fsm->createState(&LexicalAnalyzer::stringEnd, this, true), "string-end");

        // Comments
        fsm->addState(fsm->createState(&LexicalAnalyzer::comment, this, false), "comment");
        fsm->addState(fsm->createState(&LexicalAnalyzer::commentContentSingle, this, true), "comment-content-single");
        fsm->addState(fsm->createState(&LexicalAnalyzer::commentMulti, this, false), "comment-multi");
        fsm->addState(fsm->createState(&LexicalAnalyzer::commentContentMulti, this, false), "comment-content-multi");
        fsm->addState(fsm->createState(&LexicalAnalyzer::commentMultiEnd, this, false), "comment-multi-end");
        fsm->addState(fsm->createState(&LexicalAnalyzer::commentContentEnd, this, true), "comment-end");

        // Whitespace
        fsm->addState(fsm->createState(&LexicalAnalyzer::whitespace, this, true), "whitespace");

        // Period
        fsm->addState(fsm->createState(&LexicalAnalyzer::period, this, true), "period");

        // Set start state of fsm
        fsm->setInitialState("start");

    }

    void clean() {
        // Memory management, we have generated a lot of pointers
        // Gotta get rid of them or else...
        fsm->clean();
        delete fsm;
    }


    std::vector<token_struct> getTokenList() {
        std::vector<token_struct> list;

        for (auto &i : listOfTokens) {
            if (i.token != COMMENT)
                list.push_back(i);
        }

        return list;
    }

    ~LexicalAnalyzer() = default;
};

#endif
