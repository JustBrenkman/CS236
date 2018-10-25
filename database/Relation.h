#include <utility>

//
// Created by bbrenk on 10/24/18.
//

#ifndef LAB2_RELATION_H
#define LAB2_RELATION_H


#include <vector>
#include <list>
#include <string>
#include <unordered_map>

class Relation {

private:
    std::unordered_map<std::string, int> header;
    std::vector<std::vector<std::string>> rows;
    // Row definition

    template<typename ... list>
    std::list<std::pair<std::string, std::string>> *
    generatePairList(std::pair<std::string, std::string> pair, list...args);

    std::list<std::pair<std::string, std::string>> *generatePairList(std::pair<std::string, std::string> pair);

    // Private select functions to reduce a table by filtering. Makes memory management so much easier
    void select(Relation *table, std::pair<std::string, std::string> pair);

    void select(Relation *table, std::string columnName, std::string value);

public:
    Relation();

    Relation(const Relation &reftable);

    ~Relation();

    // Adds an arbitrary number of columns to the header
    template<typename ... Args>
    void addColumns(std::string first, Args... args);

    void addColumns(std::string name);

    void insertRows(std::vector<std::vector<std::string>> row);

    void insertRows(std::vector<std::string> row);

    template<typename ... pairs>
    Relation *select(std::pair<std::string, std::string> pair, pairs...args);

    Relation *select(std::list<std::pair<std::string, std::string>> pair);

    Relation *select(std::string columnName, std::string value);

    Relation *project();

    Relation *rename();

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
    return val;
}

template<typename... list>
std::list<std::pair<std::string, std::string>> *
Relation::generatePairList(std::pair<std::string, std::string> pair, list... args) {
    std::list<std::pair<std::string, std::string>> *re = generatePairList(args...);
    re->push_back(pair);
    return re;
}


#endif //LAB2_RELATION_H
