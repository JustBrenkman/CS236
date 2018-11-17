#include <utility>

//
// Created by bbrenk on 10/24/18.
//

#include <iostream>
#include "Relation.h"

Relation::Relation() = default;

//Relation::operationPrintComp = SIMPLE;
Relation::operationPrintComp Relation::opPrintComp = SIMPLE;
/**
 * Copy constructor
 * @param refTable table to copy
 */
Relation::Relation(const Relation &refTable) {
    header = std::unordered_map<std::string, int>(refTable.header);
    rows.assign(refTable.rows.begin(), refTable.rows.end());
}

/**
 * Default deconstructor
 */
Relation::~Relation() = default;

std::string Relation::getName() {
    return name;
}

bool Relation::isEmpty() {
    return rows.empty() || header.empty();
}

int Relation::getRowCount() {
    return rows.size();
}

std::vector<std::vector<std::string>> Relation::getRows() {
    return rows;
}

std::unordered_map<std::string, int> Relation::getHeadersMap() {
    return header;
}

bool Relation::isAColumn(std::string name) {
    return header.find(name) != header.end();
}

std::vector<std::string> Relation::getheaders() {
    std::vector<std::string> list;
//    std::cout << "List size:" << list.size() << std::endl;
    for (unsigned int i = 0; i < header.size(); i++)
        list.push_back("");

    for (auto &h :header) {
//        std::cout << h.second << std::endl;
        list.at(static_cast<unsigned long>(h.second - 1)) = h.first;
    }
    return list;
}

/**
 * adds a column
 * @param name of column
 */
void Relation::addColumns(std::string name) {

    if (header.find(name) != header.end())
        return;

    header[name] = static_cast<int>(header.size()) + 1;
}

void Relation::addColumns(std::vector<std::string> columns) {
    for (auto &c : columns)
        addColumns(c);
}

/**
 * Inserts a vector as a row into the table
 * @param row list of strings making up the row
 */
void Relation::insertRows(std::vector<std::string> row) {
    rows.emplace_back(row.begin(), row.begin() + header.size());
}

/**
 * Inserts a list of rows into the table
 * @param row list of rows
 */
void Relation::insertRows(std::vector<std::vector<std::string>> row) {
    for (auto &r : row) {
        if (r.size() < header.size()) {
            std::cout << "Row is smaller than header by " << header.size() - r.size() << ", adding extra value"
                      << std::endl;
            for (unsigned long i = r.size(); i < header.size(); i++) {
                r.emplace_back("");
            }
        }
        insertRows(r); // This clips the row to match header length
    }
}

/**
 * internal function to help with variadic functions
 * @param pair
 * @return
 */
std::list<std::pair<std::string, std::string>> *Relation::generatePairList(std::pair<std::string, std::string> pair) {
    auto re = new std::list<std::pair<std::string, std::string>>();
    re->push_back(pair);
    return re;
}

/**
 * internal function to help with variadic functions
 * @param col
 * @return
 */
std::vector<std::string> *Relation::generateStringList(std::string col) {
    auto re = new std::vector<std::string>();
    re->push_back(col);
    return re;
}

/**
 * Sets the operation that was performed on the table
 * Easy way to follow a series of changes
 * @param table the table being performed on
 * @param list the list of operations being performed
 */
void Relation::setSelectName(Relation *table, std::list<std::pair<std::string, std::string>> list) {
    std::string operators;
    std::string complex;
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
    complex = operators;
    operators.append(this->name);
    complex.append((this->operation == "") ? this->name : this->operation);
    operators.append(")");
    operators.append(")");
    complex.append(")");
    complex.append(")");

    table->operation = operators;
    table->operationComplex = complex;
}

/**
 * Sets the operation that was performed on the table
 * Easy way to follow a series of changes
 * @param table the table being performed on
 * @param list the list of operations being performed
 */
void Relation::setSelectName(Relation *table, std::list<std::pair<int, std::string>> list) {
    std::string operators;
    std::string complex;
    operators.append("\u03C3");
    operators.append("(");
    for (auto &l : list) {
        operators.append(std::to_string(l.first));
        operators.append("=");
        operators.append(l.second);
        operators.append("^");
    }
    operators.erase(operators.end() - 1);
    operators.append("(");
    complex = operators;
    operators.append(this->name);
    complex.append((this->operation == "") ? this->name : this->operation);
    operators.append(")");
    operators.append(")");
    complex.append(")");
    complex.append(")");

    table->operation = operators;
    table->operationComplex = complex;
}

/**
 * Sets the operation that was performed on the table
 * Easy way to follow a series of changes
 * @param table the table being performed on
 * @param list the list of operations being performed
 */
void Relation::setRenameName(Relation *table, std::list<std::pair<std::string, std::string>> list) {
    std::string operators;
    std::string complex;
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
    complex = operators;
    operators.append(this->name);
    complex.append((this->operation == "") ? this->name : this->operation);
    operators.append(")");
    operators.append(")");
    complex.append(")");
    complex.append(")");

    table->operation = operators;
    table->operationComplex = complex;
}

/**
 * Sets the operation that was performed on the table
 * Easy way to follow a series of changes
 * @param table the table being performed on
 * @param list the list of operations being performed
 */
void Relation::setProjectName(Relation *table, std::vector<std::string> list) {
    std::string operators;
    std::string complex;
    operators.append("\u03C0");
    operators.append("(");
    for (auto &l : list) {
        operators.append(l);
        operators.append(",");
    }
    operators.erase(operators.end() - 1);
    operators.append("(");
    complex = operators;
    operators.append(this->name);
    complex.append((this->operation == "") ? this->name : this->operation);
    operators.append(")");
    operators.append(")");
    complex.append(")");
    complex.append(")");

    table->operation = operators;
    table->operationComplex = complex;
}

/**
 * Sets the name of the table, default is TABLE
 * @param an name
 */
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

/**
 * This function returns a new table based on the list of select paramaters
 * input into the function call, can do both Col-Col and Col-Value selections
 * @param list this is the list of pairs that the select must be performed on
 * @return returns a new table based on the select
 */
Relation *Relation::select(std::list<std::pair<std::string, std::string>> list) {

    auto table = new Relation();

    setSelectName(table, list); // Helps make things look pretty when we print the table

    table->header = header; // Copy the header over, they don't change

    // Checks the columns in the table to see which ones are the same as the values provided
    // Fancy smanshy stuff here
    for (auto &r : rows) {
        bool flag = true;
        for (auto &p : list) {
            if (header.find(p.second) != header.end()) {
                // This is a column = column select
                if (r.at(static_cast<unsigned long>(header[p.first] - 1)) != r.at(
                        static_cast<unsigned long>(header[p.second] - 1))) {
                    flag = false;
                    break;
                }
            } else if (r.at(static_cast<unsigned long>(header[p.first]) - 1) != p.second) {
                // This is a column = value select
                flag = false;
                break;
            }
        }
        if (flag) { // if it is a match then we flag the row to add to the new table.
            std::vector<std::string> newRow;
            for (auto &p : list) {
                newRow.push_back(r.at(static_cast<unsigned long>(header[p.first]) - 1));
            }
            table->insertRows(r);
        }
    }
    table->removeDuplicateEntries();
    return table;
}

/**
 * This function returns a new table based on the list of select paramaters
 * input into the function call, can do both Col-Col and Col-Value selections
 * @param list this is the list of pairs that the select must be performed on
 * @return returns a new table based on the select
 */
Relation *Relation::select(std::list<std::pair<int, std::string>> list) {

    auto table = new Relation();

    setSelectName(table, list); // Helps make things look pretty when we print the table

    table->header = header; // Copy the header over, they don't change

    // Checks the columns in the table to see which ones are the same as the values provided
    // Fancy smanshy stuff here
    for (auto &r : rows) {
        bool flag = true;
        for (auto &p : list) {
            if (header.find(p.second) != header.end()) {
                // This is a column = column select
                if (r.at(static_cast<unsigned long>(p.first)) != r.at(
                        static_cast<unsigned long>(header[p.second] - 1))) {
                    flag = false;
                    break;
                }
            } else if (r.at(static_cast<unsigned long>(p.first)) != p.second) {
                // This is a column = value select
                flag = false;
                break;
            }
        }
        if (flag) { // if it is a match then we flag the row to add to the new table.
            std::vector<std::string> newRow;
            for (auto &p : list) {
                newRow.push_back(r.at(static_cast<unsigned long>(p.first)));
            }
            table->insertRows(r);
        }
    }
    table->removeDuplicateEntries();
    return table;
}

/**
 * Projects a table and returns a new table holding the result
 * @param table Table that holds the result
 * @param cols list of columns to project
 */
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

/**
 * Projects a table and returns a new table holding the result
 * @param col column to project
 * @return table holding the result
 */
Relation *Relation::project(std::string col) {
    auto table = new Relation();
    project(table, {std::move(col)});
    table->removeDuplicateEntries();
    return table;
}

/**
 * Projects a table and returns a new table holding the result
 * @param cols columns to project
 * @return able holding the result
 */
Relation *Relation::project(std::vector<std::string> cols) {
    auto table = new Relation();
    project(table, std::move(cols));
    table->removeDuplicateEntries();
    return table;
}

/**
 * Renames a tables columns and returns a new table holding resulting change
 * @param pair Columns to change and value to change them to
 * @return table that holds result
 */
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
    table->removeDuplicateEntries();
    return table;
}

/**
 * Renames a tables columns and returns a new table holding resulting change
 * @param columnName Column to change
 * @param value value to change them to
 * @return table that holds result
 */
Relation *Relation::rename(std::string columnName, std::string value) {
    return rename({std::make_pair(columnName, value)});
}

// Strictly a helper function, not part of the class
void getLargestColWidth(std::vector<unsigned int> &col, std::vector<std::vector<std::string>> &table) {
    for (auto &r1 : table) {
        for (unsigned int i = 0; i < col.size(); i++) {
            col.at(i) = static_cast<unsigned int>((r1.at(i).size() > col.at(i)) ? r1.at(i).size() : col.at(i));
        }
    }
}

/**
 * Prints out tables all fancy
 * @param os std::cout
 * @param table << Relation()
 * @return std::ostream
 */
std::ostream &operator<<(std::ostream &os, Relation &table) {

    os << table.name << " = "
       << ((Relation::opPrintComp == Relation::SIMPLE) ? table.operation : table.operationComplex) << std::endl;

    std::vector<unsigned int> columnWidths(table.header.size());
    std::vector<std::string> headers(table.header.size());

    for (auto &h : table.header) {
        columnWidths.at(static_cast<unsigned long>(h.second - 1)) = static_cast<int &&>(h.first.size());
        headers.at(static_cast<unsigned long>(h.second) - 1) = h.first;
    }

    getLargestColWidth(columnWidths, table.rows);

    unsigned int width = 1;
    for (auto &c : columnWidths) {
        width += c;
        width += 7;
    }

    std::string spacer = "   ";

    os << std::internal << "+" << std::setw(width - 1) << std::setfill('-') << "+" << std::endl;
    os << "|";

    for (unsigned int i = 0; i < headers.size(); i++) {
        os << spacer << std::left << std::setfill(' ') << std::setw(columnWidths.at(i)) << headers.at(i) << spacer
           << "|";
    }
    os << std::endl;
    os << "+" << std::internal << std::setw(width - 1) << std::setfill('-') << "+" << std::endl;

    for (auto &r1 : table.rows) {
        os << "|";
        for (unsigned int i = 0; i < columnWidths.size(); i++) {
            os << spacer << std::left << std::setfill(' ') << std::setw(columnWidths.at(i)) << r1.at(i) << spacer
                    << "|";
        }
        os << std::endl;
    }
    os << "+" << std::internal << std::setw(width - 1) << std::setfill('-') << "+" << std::endl;

    return os;
}

/**
 * Removes duplicates by converting to set
 */
void Relation::removeDuplicateEntries() {
//    std::sort(rows.begin(), rows.end());
//    rows.erase(std::unique(rows.begin(), rows.end(), rows.end()));
    std::set<std::vector<std::string>> s(rows.begin(), rows.end());
    rows.assign(s.begin(), s.end());
}

void Relation::setPrintCom(Relation::operationPrintComp com) {
    Relation::opPrintComp = com;
}

/*
 * Need to overload case we have some vars in here that are not some even if the tables contain the same data
 */
bool Relation::operator==(const Relation &a) {
    if (header != a.header) return false;
    if (rows != a.rows) return false;
    return true;
}