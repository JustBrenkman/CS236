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
        enum TERM_TYPE {TERM_SINGLE, GRAMMAR};
        struct term_struct {
            TERM_TYPE type;
            Ta& singularity;
            Grammar<Ta>* grammer;
        };
    private:
        std::vector<term_struct> terms;
        typedef typename std::vector<term_struct>::iterator itr;
    public:
        void addEntry(TERM_TYPE type, Ta item, Grammar<Ta>* gram) {
            term_struct entry {type, item, gram};
//            entry.type = type;
//            entry.singularity = item;
//            entry.grammer = gram;
            // Push the newly added entry to the list
            terms.push_back(entry);
        }

        bool isTermValid() {

        }
    };
private:
    std::vector<Term<T>*> listOfTerms;
    typedef typename std::vector<Term<T>*>::iterator itr;
public:
    // Proocess an input, if there isn't a possible to add it will throw an error
    void proccessTerm(T& t);

    // Creates a new grammar and returns the pointer
    static Grammar<T>* createGrammar(Term<T>* term, ...) {
        return new Grammar<T>();
    }
    // Creates a new Term and returns the pointer
    static Term<T>* createTerm() {
        return new Term<T>();
    }
};


#endif //LAB2_GRAMMAR_H
