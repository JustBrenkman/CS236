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
    public:
        void addEntry(TERM_TYPE type, Ta item, Grammar<Ta>* gram) {
            term_struct entry {type, item, gram};
            // Push the newly added entry to the list
            terms.push_back(entry);
        }

        bool isTermValid(Ta &ta) {
            if (pos >= terms.size())
                return true;

            term_struct term = terms.at(pos);

            switch (term.type) {
                case TERMINAL:
                    if (ta == term.singularity) {
                        pos++;
                    }
                    break;
                case GRAMMAR:
                    if (term.grammer->proccessTerm(ta)) {
                        pos++;
                    }
                    break;
                case EPSOLON:

                    break;
                case LAMBDA:

                    break;
                default:
                    throw std::string("Error");
            }

            return pos >= terms.size();
        }

        bool isTermValid(std::vector<Ta> &ta, int &index) {
            int position = 0;
            bool passes = true;

            for (; position < terms.size(); position++) {

                term_struct term = terms.at(position);

                switch (term.type) {
                    case TERMINAL:
                        if (ta.at(index) == term.singularity) {
                            index++;
                        } else {
                            return false;
                        }
                        break;
                    case GRAMMAR:
                        if (term.grammer->proccessList(ta, index)) {

                        } else {
                            return false;
                        }
                        break;
                    case EPSOLON:

                        break;
                    case LAMBDA:

                        break;
                    default:
                        throw GrammarException(index, "Undefined", LexicalAnalyzer::enumToString(ta.at(index)));
                }
            }

            return passes;
        }
    };
private:
    std::vector<Term<T>*> listOfTerms;
    int pos = 0;
    bool acceptsLambda = false;
    std::string name;
public:
    explicit Grammar(std::string name) {
        this->name = name;
    }
    // Proocess an input, if there isn't a possible to add it will throw an error
    bool proccessTerm(T &t) {

        if (pos >= listOfTerms.size())
            throw std::string("Error - out of bounds");

        if (listOfTerms.at(pos)->isTermValid(t)) {
            pos++;
            if (pos > listOfTerms.size())
                return true;
        }

        return false;
    }

    bool proccessList(std::vector<T> &t, int &index) {
        int position = 0;
        bool found = false;

        for (; position < listOfTerms.size(); position++) {
            if (position > listOfTerms.size())
                throw std::string("Error - out of bounds");

            if (listOfTerms.at(position)->isTermValid(t, index)) {
                return true;
            } else {
                continue;
            }
        }

        if (!acceptsLambda)
            throw GrammarException(index, "Undefined", LexicalAnalyzer::enumToString(t.at(index)));

        return true;
    }

    void addLambdaTerm() {
        acceptsLambda = true;
    }

    void addTermToGrammar(Term<T> *term) {
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
