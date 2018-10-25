//
// Created by bbrenk on 10/24/18.
//

#include <iostream>
#include "Relation.h"

Relation::Relation() = default;

Relation::Relation(const Relation &refTable) {
    header = refTable.header;
}

Relation::~Relation() = default;


void Relation::addColumns(std::string name) {

    if (header.find(name) != header.end())
        return;

    header[name] = static_cast<int>(header.size()) + 1;
}

void Relation::insertRows(std::vector<std::string> row) {
    rows.push_back(row);
}

void Relation::insertRows(std::vector<std::vector<std::string>> row) {
    for (auto &r : row) {
        insertRows(r);
    }
}

std::list<std::pair<std::string, std::string>> *Relation::generatePairList(std::pair<std::string, std::string> pair) {
    auto re = new std::list<std::pair<std::string, std::string>>();
    re->push_back(pair);
    return re;
}

/*****************************************************************
 *
 *      Select Functions
 *
 ******************************************************************/

/**
 * Select function - just calls the select(std::list<std::pair<std::string, std::string>> list)
 * @param list - defines a list of pairs to do the select query on
 * @return returns the database based on the list of pairs
 */
Relation *Relation::select(std::string columnName, std::string value) {
    return select({std::make_pair(columnName, value)});
}

Relation *Relation::select(std::list<std::pair<std::string, std::string>> list) {

    auto table = new Relation();

    for (auto &p : list) {
        if (header.find(p.first) != header.end()) {
            table->addColumns(p.second);
        } else {
            throw std::string("Column does not exist");
        }
    }

    for (auto &r : rows) {
        bool flag = true;
        for (auto &p : list) {
            if (r.at(static_cast<unsigned long>(header[p.first]) - 1) != p.second) {
                flag = false;
                break;
            }
        }

        if (flag) {
            std::vector<std::string> newRow;
            for (auto &p : list) {
                newRow.push_back(r.at(static_cast<unsigned long>(header[p.first]) - 1));
            }
            table->insertRows(newRow);
        }
    }

    return table;
}

void Relation::select(Relation *table, std::pair<std::string, std::string> pair) {
    select(table, pair.first, pair.second);
}

void Relation::select(Relation *table, std::string columnName, std::string value) {
    if (table) {
        std::cout << "Table is empty, attempting to copy" << std::endl;
    }

    std::cout << "Do selection query" << std::endl;
}