#include <utility>

/*
 * Purpose: This is a basic table class that can perform select, project and rename relational algebra functions
 * Author: Ben Brenkman
 * Date: 10/25/2018
 */

//Letter   Description  Escape-Sequence
//-------------------------------------
//        A        Alpha        \u0391
//        B        Beta         \u0392
//        Γ        Gamma        \u0393
//        Δ        Delta        \u0394
//        Ε        Epsilon      \u0395
//        Ζ        Zeta         \u0396
//        Η        Eta          \u0397
//        Θ        Theta        \u0398
//        Ι        Iota         \u0399
//        Κ        Kappa        \u039A
//        Λ        Lambda       \u039B
//        Μ        Mu           \u039C
//        Ν        Nu           \u039D
//        Ξ        Xi           \u039E
//        Ο        Omicron      \u039F
//        Π        Pi           \u03A0
//        Ρ        Rho          \u03A1
//        Σ        Sigma        \u03A3
//        Τ        Tau          \u03A4
//        Υ        Upsilon      \u03A5
//        Φ        Phi          \u03A6
//        Χ        Chi          \u03A7
//        Ψ        Psi          \u03A8
//        Ω        Omega        \u03A9

//Letter   Description  Escape-Sequence
//-------------------------------------
//        α        Alpha        \u03B1
//        β        Beta         \u03B2
//        γ        Gamma        \u03B3
//        δ        Delta        \u03B4
//        ε        Epsilon      \u03B5
//        ζ        Zeta         \u03B6
//        η        Eta          \u03B7
//        θ        Theta        \u03B8
//        ι        Iota         \u03B9
//        κ        Kappa        \u03BA
//        λ        Lambda       \u03BB
//        μ        Mu           \u03BC
//        ν        Nu           \u03BD
//        ξ        Xi           \u03BE
//        ο        Omicron      \u03BF
//        π        Pi           \u03C0
//        ρ        Rho          \u03C1
//        σ        Sigma        \u03C3
//        τ        Tau          \u03C4
//        υ        Upsilon      \u03C5
//        φ        Phi          \u03C6
//        χ        Chi          \u03C7
//        ψ        Psi          \u03C8
//        ω        Omega        \u03C9

#ifndef LAB2_RELATION_H
#define LAB2_RELATION_H


#include <vector>
#include <list>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <iomanip>
#include <set>

class Relation {
public:
    enum operationPrintComp {
        SIMPLE, CHAINED
    };
private:
    std::unordered_map<std::string, int> header;
    std::vector<std::vector<std::string>> rows;
    std::string name = "TABLE";
    std::string operation = "";
    std::string operationComplex = "";
    static operationPrintComp opPrintComp;

    template<typename ... list>
    std::list<std::pair<std::string, std::string>> *
    generatePairList(std::pair<std::string, std::string> pair, list...args);
    std::list<std::pair<std::string, std::string>> *generatePairList(std::pair<std::string, std::string> pair);

    template<typename ... params>
    std::vector<std::string> *
    generateStringList(std::string col, params...args);

    std::vector<std::string> *generateStringList(std::string col);

    // Private select functions to reduce a table by filtering. Makes memory management so much easier
    void project(Relation *table, std::vector<std::string> cols);

    void setSelectName(Relation *table, std::list<std::pair<std::string, std::string>> list);

    void setSelectName(Relation *table, std::list<std::pair<int, std::string>> list);

    void setRenameName(Relation *table, std::list<std::pair<std::string, std::string>> list);

    void setProjectName(Relation *table, std::vector<std::string> list);

public:
    Relation();
    Relation(const Relation &reftable);
    ~Relation();

    // Adds an arbitrary number of columns to the header
    template<typename ... Args>
    void addColumns(std::string first, Args... args);

    void addColumns(std::vector<std::string> columns);
    void addColumns(std::string name);

    // Row insertion functions
    void insertRows(std::vector<std::vector<std::string>> row);
    void insertRows(std::vector<std::string> row);

    // Select functions
    template<typename ... pairs>
    Relation *select(std::pair<std::string, std::string> pair, pairs...args);
    Relation *select(std::list<std::pair<std::string, std::string>> pair);

    Relation *select(std::list<std::pair<int, std::string>> pair);
    Relation *select(std::string columnName, std::string value);

    // Project Functions.find(queryCol.at(j))
    template<typename ... param>
    Relation *project(std::string colName, param... args);
    Relation *project(std::vector<std::string> cols);
    Relation *project(std::string col);

    // Rename functions
    template<typename ... pairs>
    Relation *rename(std::pair<std::string, std::string> pair, pairs...args);
    Relation *rename(std::list<std::pair<std::string, std::string>> pair);
    Relation *rename(std::string columnName, std::string value);

    friend std::ostream &operator<<(std::ostream &os, Relation &table);

    bool operator==(const Relation &a);

    void setName(std::string an);

    std::string getName();
    void removeDuplicateEntries();

    std::vector<std::string> getheaders();

    bool isEmpty();

    int getRowCount();

    std::vector<std::vector<std::string>> getRows();

    std::unordered_map<std::string, int> getHeadersMap();

    static void setPrintCom(Relation::operationPrintComp com);
};

// Adds an arbitrary number of columns
template<typename... Args>
void Relation::addColumns(std::string first, Args... args) {

    addColumns(std::move(first));
    addColumns(args...);

}

template<typename... pairs>
Relation *Relation::select(std::pair<std::string, std::string> pair, pairs... args) {
    std::list<std::pair<std::string, std::string>> *list = generatePairList(pair, args...);
    list->reverse();
    auto val = select(*list);
    delete list;
    val->removeDuplicateEntries();
    return val;
}

template<typename... list>
std::list<std::pair<std::string, std::string>> *
Relation::generatePairList(std::pair<std::string, std::string> pair, list... args) {
    std::list<std::pair<std::string, std::string>> *re = generatePairList(args...);
    re->push_back(pair);
    return re;
}

template<typename... params>
std::vector<std::string> *Relation::generateStringList(std::string col, params... args) {
    std::vector<std::string> *re = generateStringList(args...);
    re->push_back(col);
    return re;
}

template<typename... param>
Relation *Relation::project(std::string colName, param... args) {
    std::vector<std::string> *list = generateStringList(colName, args...);
    std::reverse(list->begin(), list->end());
    auto val = project(*list);
    delete list;
    val->removeDuplicateEntries();
    return val;
}

template<typename... pairs>
Relation *Relation::rename(std::pair<std::string, std::string> pair, pairs... args) {
    std::list<std::pair<std::string, std::string>> *list = generatePairList(pair, args...);
    list->reverse();
    auto val = rename(*list);
    delete list;
    val->removeDuplicateEntries();
    return val;
}

#endif //LAB2_RELATION_H
