/**
 *
 * Class Grammar: This is a generic class to help construct grammars. A grammar is simply a list of terms and
 * other grammars that define a language. The terms arre simply each piece and its ability to call on itself
 * recursively i.e. a grammar can call on a grammar -- to check the validity of a sentence in that grammar
 *
 * All it takes is a single grammar built from the bottom up to produce such a result.
 *
 * Author: Ben Brenkman
 * Date: 10/05/2018
 */

#ifndef LAB2_GRAMMAR_H
#define LAB2_GRAMMAR_H

#include <vector>
#include "LexicalAnalyzer.h"
#include <iostream>
#include "GrammarException.h"

template<typename T>
class Grammar {
public:
    /*
     * This is a template class of a term, which can a list of definitions
     * Each definition is either a singularity(a definite value we can compare against)
     * Or a grammar which will then be called recursively
     */
    template<typename Ta>
    class Term {
    public:
        enum TERM_TYPE {
            TERMINAL, GRAMMAR, EPSOLON, LAMBDA
        };
        struct term_struct {
            TERM_TYPE type;
            Ta singularity;
            Grammar<Ta>* grammer;
        };
    private:
        std::vector<term_struct> terms;
        int pos = 0;
        std::string parentName;
        bool isMainGrammar = false;
    public:
        void addEntry(TERM_TYPE type, Ta item, Grammar<Ta>* gram) {
            term_struct entry {type, item, gram};
            // Push the newly added entry to the list
            terms.push_back(entry);
        }

        void setParetName(std::string name) {
            parentName = name;
        }

        bool isTermValid(std::vector<Ta> &ta, int &index) {
            int position = 0;
            for (; position < terms.size(); position++) {

                term_struct term = terms.at(position);

                switch (term.type) {
                    case TERMINAL:
                        if (ta.at(index) == term.singularity) {
                            index++;
                        } else {
                            if (position > 0)
                                throw GrammarException(index, "Undefined", LexicalAnalyzer::enumToString(ta.at(index)));
                            return false;
                        }
                        break;
                    case GRAMMAR:
                        if (term.grammer->proccessList(ta, index)) {
                        } else {
                            if (position > 0)
                                throw GrammarException(index, "Undefined", LexicalAnalyzer::enumToString(ta.at(index)));
                            return false;
                        }
                        break;
                    default:
                        break;
                }
            }

            return true;
        }
    };
private:
    std::vector<Term<T>*> listOfTerms;
    bool acceptsLambda = false;
    std::string name;
public:

    explicit Grammar(std::string name) {
        this->name = name;
    }

    bool proccessList(std::vector<T> &t, int &index) {
        int position = 0;
        bool flag = false;

        for (; position < listOfTerms.size(); position++) {
            if (position > listOfTerms.size())
                throw std::string("Error - out of bounds");

            if (listOfTerms.at(position)->isTermValid(t, index)) {
                    return true;
                } else {
                    continue;
                }
        }

        return acceptsLambda;

    }

    void addLambdaTerm() {
        acceptsLambda = true;
    }

    void addTermToGrammar(Term<T> *term) {
        term->setParetName(this->name);
        listOfTerms.push_back(term);
    }

    // Creates a new grammar and returns the pointer
    static Grammar<T> *createGrammar(std::string name) {
        auto *gram = new Grammar<T>(name);
        return gram;
    }
    // Creates a new Term and returns the pointer
    static Term<T>* createTerm() {
        return new Term<T>();
    }

    void clean() {
        for (auto &term : listOfTerms) {
            delete term;
        }
    }
};


#endif //LAB2_GRAMMAR_H
