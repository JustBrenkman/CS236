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
        list.emplace_back("");

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
    complex.append((this->operation.empty()) ? this->name : this->operation);
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
    complex.append((this->operation.empty()) ? this->name : this->operation);
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
    complex.append((this->operation.empty()) ? this->name : this->operation);
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
    complex.append((this->operation.empty()) ? this->name : this->operation);
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

/**
 * Unions two tables using a natural union
 * @param table - table to union
 * @return - new table holding the result
 */
Relation *Relation::Union(Relation *table) {
    // First check to see if it is union compatible
//    bool comp = true;
//    if (getheaders().size() != table->getheaders().size())
//    for (auto &e : getheaders()) {
//        bool found = false;
//        for (auto &o : table->getheaders()) {
//            if (e == o) found = true;
//        }
//        if (!found) comp = false;
//    }
//
//    if (comp) {
//        auto result = new Relation();
//        result->header = header;
//        result->insertRows(rows);
//        for (auto & r : table->rows) {
//            std::vector<std::string> rowToAdd;
//            for (auto & h : getheaders()) {
//                rowToAdd.push_back(r.at(table->header[h] - 1));
//            }
//            result->insertRows(rowToAdd);
//        }
//        result->removeDuplicateEntries();
//        return result;
//    } else {
//        return nullptr;
//    }
//    reorder();
    auto result = new Relation();
    if (header.size() == table->header.size()) {
        result->setName(table->getName());
//        for (auto &c : getheaders()) {
//            result->addColumns(c);
//        }
        result->addColumns(getheaders());
        result->insertRows(getRows());
        result->insertRows(table->getRows());
        result->removeDuplicateEntries();
//     insertRows(table->getRows());
    }
    return result;
}

/**
 * Joins two tables
 * @param table - table to join
 * @return - new table that holds the result
 */
Relation *Relation::join(Relation *table) {
    auto result = new Relation();
    // This is the crazy one
    // Turn the tables into hashmaps for speed
    // First find the columns in both tables that have the same name
    std::vector<std::string> headers = getheaders();
    std::vector<std::string> col;
    for (auto &h : headers) {
        if (table->header.find(h) != table->header.end()) {
            col.push_back(h);
        }
    }

    result->header = header;
    for (auto &h : table->getheaders()) {
        bool canAdd = true;
        for (auto &c : col) {
            if (c == h) canAdd = false;
        }
        if (canAdd) result->header[h] = result->header.size() + 1;
    }

    // Second check the values, if they are equivalent, then they are the same
    for (auto &r : rows) {
        for (auto &ri : table->rows) {
            bool addCol = true;
            if (col.size() > 0) {
                for (auto &c : col) {
                    if (r.at(header[c] - 1) != ri.at(table->header[c] - 1)) addCol = false;
                }

                if (addCol) {
                    std::vector<std::string> rowToAdd;
                    for (auto &rj : result->getheaders()) {
                        if (header.find(rj) != header.end()) {
                            rowToAdd.push_back(r.at(header[rj] - 1));
                        } else if (table->header.find(rj) != table->header.end()) {
                            rowToAdd.push_back(ri.at(table->header[rj] - 1));
                        }
                    }

                    result->insertRows(rowToAdd);
                }
            } else {
                std::vector<std::string> rowToAdd;
                rowToAdd.reserve(r.size() + ri.size());
                rowToAdd.insert(rowToAdd.end(), r.begin(), r.end());
                rowToAdd.insert(rowToAdd.end(), ri.begin(), ri.end());
                result->insertRows(rowToAdd);
            }
        }
    }
    return result;
}

std::vector<std::vector<int>> Relation::getSameColumns(Relation* table) {
    std::vector<int> simRow1, simRow2;
    for (int i = 0; i < getheaders().size(); i++) {
        if (table->header.find(getheaders().at(i)) != table->header.end()) {
            simRow1.push_back(i);
            simRow2.push_back(table->header[getheaders().at(i)]);
        }
    }
    std::vector<std::vector<int>> result;
    result.push_back(simRow1);
    result.push_back(simRow2);
    return result;
}

Relation *Relation::hashJoin(Relation *table) {
    unsigned int size1 = this->size();
    unsigned int size2 = table->size();
    std::vector<std::vector<std::string>> a;
    std::vector<std::vector<std::string>> b;
    size_t columna;
    size_t columnb;
    std::vector<std::vector<int>> columnMatches = getSameColumns(table);

    if (size1 <= size2) {
        a = getRows();
        b = table->getRows();
        columna = 1;
        columnb = 1;
    } else {
        b = getRows();
        a = table->getRows();
        columnb = 1;
        columna = 1;
    }

    std::vector<std::unordered_multimap<std::string, size_t >> hashmaps;
    std::unordered_multimap<std::string, size_t> hashmap;
    // hash
    for (size_t j = 0; j < columnMatches.at(0).size(); ++j) {
        std::unordered_multimap<std::string, size_t> hashmap;
        for(size_t i = 0; i < a.size(); ++i) {
            hashmap.insert(std::make_pair(a[i][columna], i));
        }
        hashmaps.push_back(hashmap);
    }
//    for(size_t i = 0; i < a.size(); ++i) {
//        hashmap.insert(std::make_pair(a[i][columna], i));
//    }
    // map
    std::vector<std::vector<std::string>> result;
    for(size_t i = 0; i < b.size(); ++i) {
        for (auto &h: hashmaps) {
            auto range = h.equal_range(b[i][columnb]);
            for(auto it = range.first; it != range.second; ++it) {
                std::vector<std::vector<std::string>>::value_type row;
                row.insert(row.end() , a[it->second].begin() , a[it->second].end());
                row.insert(row.end() , b[i].begin()          , b[i].end());
                result.push_back(std::move(row));
            }
        }
    }

    auto re = new Relation();
    re->addColumns(getheaders());
    re->addColumns(table->getheaders());
    re->insertRows(result);
//    re->removeDuplicateEntries();
    return re;
}

/**
 * This will reorder the columns in the relation
 */
void Relation::reorder() {
    // First reorder the header
    std::vector<std::string> headers = getheaders();
    std::sort(headers.begin(), headers.end());
    std::unordered_map<std::string, int> header_old = header;

    int count = 1;
    for (auto &h : headers) {
        header[h] = count;
        std::cout << h;
        count++;
    }
}

unsigned int Relation::size() {
    unsigned int totalSize = 0;
    for (auto &r: rows)
        totalSize += r.size();
    return totalSize;
}