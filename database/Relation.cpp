#include <utility>

//
// Created by bbrenk on 10/24/18.
//

#include <iostream>
#include "Relation.h"

Relation::Relation() = default;

Relation::Relation(const Relation &refTable) {
    header = std::unordered_map<std::string, int>(refTable.header);
//    rows = std::vector<std::vector<std::string>>(refTable.rows);

    rows.assign(refTable.rows.begin(), refTable.rows.end());

//    for (auto &r1 : refTable.rows) {
//        std::vector<std::string> row;
//        row.reserve(r1.size());
//        for (auto &r2 : r1) {
//            row.push_back(r2);
//        }
//        rows.push_back(row);
//    }

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
        if (r.size() < header.size()) {
            std::cout << "Row is smaller than header by " << header.size() - r.size() << ", adding extra value"
                      << std::endl;
            for (unsigned long i = r.size(); i < header.size(); i++) {
                r.emplace_back("");
            }
        }

        insertRows(r);
    }
}

std::list<std::pair<std::string, std::string>> *Relation::generatePairList(std::pair<std::string, std::string> pair) {
    auto re = new std::list<std::pair<std::string, std::string>>();
    re->push_back(pair);
    return re;
}

std::vector<std::string> *Relation::generateStringList(std::string col) {
    auto re = new std::vector<std::string>();
    re->push_back(col);
    return re;
}

void Relation::setSelectName(Relation *table, std::list<std::pair<std::string, std::string>> list) {
    std::string operators;
    operators.append("\u03C3");
    operators.append("(");
    for (auto &l : list) {
        operators.append(l.first);
        operators.append("=");
        operators.append(l.second);
        operators.append("^");
    }
    operators.erase(operators.end() - 1);
    operators.append("(");
    operators.append(this->name);
    operators.append(")");
    operators.append(")");

    table->operation = operators;
}

void Relation::setRenameName(Relation *table, std::list<std::pair<std::string, std::string>> list) {
    std::string operators;
    operators.append("\u03C1");
    operators.append("(");
    for (auto &l : list) {
        operators.append(l.first);
        operators.append("\u2190");
        operators.append(l.second);
        operators.append(",");
    }
    operators.erase(operators.end() - 1);
    operators.append("(");
    operators.append(this->name);
    operators.append(")");
    operators.append(")");

    table->operation = operators;
}

void Relation::setProjectName(Relation *table, std::vector<std::string> list) {
    std::string operators;
    operators.append("\u03C0");
    operators.append("(");
    for (auto &l : list) {
        operators.append(l);
        operators.append(",");
    }
    operators.erase(operators.end() - 1);
    operators.append("(");
    operators.append(this->name);
    operators.append(")");
    operators.append(")");

    table->operation = operators;
}

void Relation::setName(std::string an) {
    name = std::move(an);
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

    setSelectName(table, list);

//    for (auto &p : list) {
//        if (header.find(p.first) != header.end()) {
//            table->addColumns(p.second);
//        } else {
//            throw std::string("Column does not exist");
//        }
//    }

    table->header = header;

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
            table->insertRows(r);
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


void Relation::project(Relation *table, std::vector<std::string> cols) {
    setProjectName(table, cols);

    for (auto &col : cols) {
        if (header.find(col) != header.end()) {
            table->addColumns(col);
        } else {
            throw std::string("Unknown Column name, check your spelling");
        }
    }

    for (auto &r : rows) {
        std::vector<std::string> row;
        row.reserve(cols.size());
        for (auto &c : cols) {
            row.push_back(r.at(static_cast<unsigned long>(header[c] - 1)));
        }
        table->insertRows(row);
    }
}

Relation *Relation::project(std::string col) {
    auto table = new Relation();
    project(table, {std::move(col)});
    return table;
}

Relation *Relation::project(std::vector<std::string> cols) {
    auto table = new Relation();
    project(table, std::move(cols));
    return table;
}

Relation *Relation::rename(std::list<std::pair<std::string, std::string>> pair) {
    auto table = new Relation(*this);

    setRenameName(table, pair);

    for (auto &p : pair) {
        if (table->header.find(p.first) != table->header.end()) {
            int temp = table->header[p.first];
            table->header.erase(p.first);
            table->header[p.second] = temp;
        }
    }
    return table;
}

Relation *Relation::rename(std::string columnName, std::string value) {
    return rename({std::make_pair(columnName, value)});
}

std::ostream &operator<<(std::ostream &os, Relation &table) {

    os << table.name << " = " << table.operation << std::endl;

    std::vector<int> columnWidths(table.header.size());
    std::vector<std::string> headers(table.header.size());

    for (auto &h : table.header) {
        columnWidths.at(static_cast<unsigned long>(h.second - 1)) = static_cast<int &&>(h.first.size());
        headers.at(static_cast<unsigned long>(h.second) - 1) = h.first;
    }

    for (auto &r1 : table.rows) {
        for (unsigned int i = 0; i < r1.size(); i++) {
            columnWidths.at(i) = static_cast<int>((r1.at(i).size() > columnWidths.at(i)) ? r1.at(i).size()
                                                                                         : columnWidths.at(i));
        }
    }

    unsigned int width = 1;
    for (auto &c : columnWidths) {
        width += c;
        width += 7;
    }

    std::string spacer = "   ";

    os << std::internal << "+" << std::setw(width - 1) << std::setfill('-') << "+" << std::endl;
    os << "|";

    for (unsigned int i = 0; i < headers.size(); i++) {
//        os << spacer << h << spacer << "|";
        os << spacer << std::left << std::setfill(' ') << std::setw(columnWidths.at(i)) << headers.at(i) << spacer
           << "|";
    }
    os << std::endl;
    os << "+" << std::internal << std::setw(width - 1) << std::setfill('-') << "+" << std::endl;

    for (auto &r1 : table.rows) {
        os << "|";
        for (unsigned int i = 0; i < r1.size(); i++) {
            os << spacer << std::left << std::setfill(' ') << std::setw(columnWidths.at(i)) << r1.at(i) << spacer
               << "|";
        }
        os << std::endl;
    }
    os << "+" << std::internal << std::setw(width - 1) << std::setfill('-') << "+" << std::endl;

    return os;
}