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
            Grammar<Ta> *grammer;
        };
    private:
        std::vector<term_struct> terms;
        std::string parentName;
    public:
        // adds another entry into the terms list
        void addEntry(TERM_TYPE type, Ta item, Grammar<Ta> *gram) {
            term_struct entry{type, item, gram};
            // Push the newly added entry to the list
            terms.push_back(entry);
        }

        // Sets the name of the grammar it is in
        void setParetName(std::string name) {
            parentName = name;
        }

        // Super duper complex function!
        // Jk it just checks to see all the terms in the list of terms are satisfied by the input
        // WARNING RECURSIVE
        bool isTermValid(std::vector<Ta> &ta, unsigned int &index) {
            unsigned int position = 0;
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
    // List of terms in the grammar
    std::vector<Term<T> *> listOfTerms;
    // This will dtermine if the grammar accepts lambda or not
    bool acceptsLambda = false;
    // Name of the grammar usefule for debugging
    std::string name;
public:

    // Name assignment is given in the constructor, mainly for debugging
    explicit Grammar(std::string name) {
        this->name = name;
    }

    // Super duper complex function!
    // Jk it just checks to see there is a term in the list of terms that is satisfied by the input
    bool proccessList(std::vector<T> &t, unsigned int &index) {
        unsigned int position = 0;
        // checks every term in list of terms
        for (; position < listOfTerms.size(); position++) {

            if (position > listOfTerms.size())
                throw std::string("Error - out of bounds"); // Just in case ;)

            if (listOfTerms.at(position)->isTermValid(t, index)) {
                return true; // Only needs to find one term that it satisfied
            } else {
                continue;
            }
        }

        return acceptsLambda;

    }

    // Adds a lambda term to the list of terms
    void addLambdaTerm() {
        acceptsLambda = true;
    }

    // Adds term to grammar and sets the terms parent to the grammars name
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
    static Term<T> *createTerm() {
        return new Term<T>();
    }

    // Memory management :)
    void clean() {
        for (auto &term : listOfTerms) {
            delete term;
        }
    }
};

#endif //LAB2_GRAMMAR_H
