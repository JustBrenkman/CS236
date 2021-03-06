//
// Created by bbrenk on 11/2/18.
//

#include "Interpreter.h"

Interpreter::~Interpreter() = default;

Interpreter *Interpreter::generateRelations(Schemes &schemes, Facts &facts, Rules& rules) {
    auto interp = new Interpreter();

    for (auto &s : schemes.getSchemes()) {
        auto relation = new Relation();
        relation->addColumns(s->getColumnNames());
        relation->setName(s->getName());

        for (auto &f : facts.getFacts()) {
            if (f->getName() == s->getName()) {
                relation->insertRows(f->listTheStrings());
            }
        }

        interp->addRelation(relation);
    }

    // Process every single rule
//    std::cout << "Processing rules" << std::endl;
    for (auto &r : rules.getRules())
        interp->processRule(r);

    return interp;
}

void Interpreter::processRule(Rule *rule) {
//    std::cout << "Processing Rule" << std::endl;
    std::vector<Relation*> results;
    for (auto &p : rule->getPredicates()) {
//        std::cout << "Processing predicate: " << *p << std::endl;
        auto result = processPredicateOnTable(p, getTableByName(p->getName()));
        auto result1 = renameAndProject(p, result);
        results.push_back(result1);
        delete result;
//        std::cout << *result1 << std::endl;
    }

    Relation* re = results.at(0);
    if (results.size() > 1) {
        for (unsigned int i = 1; i < results.size(); i++) {
            auto temp = re->join(results.at(i));
            delete re;
            re = temp;
        }
    }
    Relation* final = renameAndProject(rule->getHeadPredicate(), re);
//    std::cout << "Result: " << *final << std::endl << rule->getHeadPredicate()->getName() << std::endl;
    Relation* finalJoined;

    bool found = false;
    for (auto &t : relations) {
        if (rule->getHeadPredicate()->getName() == t->getName()) {
//            std::cout << *t << std::endl;
//            std::cout << *final << std::endl;
            std::string name = t->getName();
            t = t->Union(final);
            t->setName(name);
            found = true;
            break;
        }
    }

    if (!found) {
        final->setName(rule->getHeadPredicate()->getName());
        relations.push_back(final);
//        std::cout << "Results: " << *final << std::endl;
    }
//    std::cout << *finalJoined << std::endl;
}

Relation* Interpreter::getTableByName(std::string name) {
    Relation* table = nullptr;
    for (auto &t : relations) {
        if (name == t->getName()) {
            table = t;
            break;
        }
    }
    return table;
}

Relation *Interpreter::proccessQueryOnTable(Query *q, Relation *t) {
    std::list<std::pair<std::string, std::string>> list; // Select parameters
    std::vector<std::string> headers = t->getheaders(); // the headers of the table
    std::unordered_map<std::string, std::string> variables;
    for (unsigned int i = 0; i < q->getParams().size(); i++) {
        // Check if they are variables
        if (q->getParams().at(i).find('\'') != std::string::npos ||
            t->isAColumn(q->getParams().at(i))) { // Check if it is a constant or not
            list.emplace_back(std::make_pair(headers.at(i), ((q->getParams().at(i).find('\'') != std::string::npos)
                                                             ? q->getParams().at(i) : headers.at(i))));
        } else {
            // It is a variable
            if (variables.find(q->getParams().at(i)) != variables.end()) {
                list.emplace_back(std::make_pair(variables[q->getParams().at((i))], headers.at(i)));
            } else {
                variables[q->getParams().at(i)] = headers.at(i);
            }
        }
    }
    std::cout << *q << "? ";
    auto result = t->select(list);
    std::cout << ((result->isEmpty()) ? "No" : "Yes(" + std::to_string(result->getRowCount()) + ")")
              << std::endl;

    return result;
}

Relation *Interpreter::processPredicateOnTable(Predicate *q, Relation *t) {
    std::list<std::pair<std::string, std::string>> list; // Select parameters
    std::vector<std::string> headers = t->getheaders(); // the headers of the table
    std::unordered_map<std::string, std::string> variables;
    for (unsigned int i = 0; i < q->getParams().size(); i++) {
        // Check if they are variables
        if (q->getParams().at(i).find('\'') != std::string::npos ||
            t->isAColumn(q->getParams().at(i))) { // Check if it is a constant or not
            list.emplace_back(std::make_pair(headers.at(i), ((q->getParams().at(i).find('\'') == std::string::npos)
                                                             ? q->getParams().at(i) : headers.at(i))));
        } else {
            // It is a variable
            if (variables.find(q->getParams().at(i)) != variables.end()) {
                list.emplace_back(std::make_pair(variables[q->getParams().at((i))], headers.at(i)));
            } else {
                variables[q->getParams().at(i)] = headers.at(i);
            }
        }
    }
//    std::cout << *q << "? ";
//    for (auto &e : list) {
//        std::cout << e.first << ", " << e.second << std::endl;
//    }
    auto result = t->select(list);
//    std::cout << ((result->isEmpty()) ? "No" : "Yes(" + std::to_string(result->getRowCount()) + ")")
//              << std::endl;

    return result;
}

Relation *Interpreter::renameAndProject(Query *query, Relation *table) {
    std::vector<std::string> projectCol;
    std::list<std::pair<std::string, std::string>> renameCol;
    std::vector<std::string> headers = table->getheaders(); // the headers of the table
    // First step to the project of the columns we need
    for (unsigned int i = 0; i < query->getParams().size(); i++) {
        if (query->getParams().at(i).find('\'') == std::string::npos) {
            projectCol.push_back(query->getParams().at(i));
            if (!table->isAColumn(query->getParams().at(i))) {
                renameCol.emplace_back(headers.at(i), query->getParams().at(i));
            }
        }
    }

    std::set<std::string> s(projectCol.begin(), projectCol.end());
    projectCol.assign(s.begin(), s.end());

    auto rename = table->rename(renameCol);
    auto result = rename->project(projectCol);
    delete rename;

    return result;
}

Relation *Interpreter::renameAndProject(Predicate *query, Relation *table) {
    std::vector<std::string> projectCol;
    std::list<std::pair<std::string, std::string>> renameCol;
    std::vector<std::string> headers = table->getheaders(); // the headers of the table
    // First step to the project of the columns we need
    for (unsigned int i = 0; i < query->getParams().size(); i++) {
        if (query->getParams().at(i).find('\'') == std::string::npos) {
            projectCol.push_back(query->getParams().at(i));
            if (!table->isAColumn(query->getParams().at(i))) {
                renameCol.emplace_back(headers.at(i), query->getParams().at(i));
            }
        }
    }

    std::set<std::string> s(projectCol.begin(), projectCol.end());
    projectCol.assign(s.begin(), s.end());

    auto rename = table->rename(renameCol);
    auto result = rename->project(projectCol);
    delete rename;

    return result;
}

Relation *Interpreter::renameAndProject(HeadPredicate *query, Relation *table) {
    std::vector<std::string> projectCol;
    std::list<std::pair<std::string, std::string>> renameCol;
    std::vector<std::string> headers = table->getheaders(); // the headers of the table
    // First step to the project of the columns we need
    for (unsigned int i = 0; i < query->getParams().size(); i++) {
        if (query->getParams().at(i).find('\'') == std::string::npos) {
            projectCol.push_back(query->getParams().at(i));
            if (!table->isAColumn(query->getParams().at(i))) {
                renameCol.emplace_back(headers.at(i), query->getParams().at(i));
            }
        }
    }

    std::set<std::string> s(projectCol.begin(), projectCol.end());
    projectCol.assign(s.begin(), s.end());

    auto rename = table->rename(renameCol);
    auto result = rename->project(projectCol);
    delete rename;

    return result;
}

void Interpreter::proccessQueries(Interpreter *interpreter, Queries queries) {
    for (auto &q : queries.getQueries()) { // Do this for all queries
        for (auto &t : interpreter->relations) { // Find the relation we want to do the query on
            if (t->getName() == q->getName()) { // Conduct query on this table
                auto select = interpreter->proccessQueryOnTable(q, t);
                auto result = interpreter->renameAndProject(q, select);
                delete select;
                if (!result->isEmpty())
                    interpreter->printResults(q, result);
                delete result;
            }
        }
    }
}

void Interpreter::printResults(Query *query, Relation *table) {
    std::unordered_map<std::string, int> headers = table->getHeadersMap();
    std::vector<std::vector<std::string>> rows = table->getRows();
    std::vector<std::string> queryCol = query->getParams();
    std::vector<std::string> resultQue;
    for (auto &row : rows) {
        bool addSpacer = false;
        std::string result;
        std::unordered_map<std::string, std::string> variables;
        for (auto &j : queryCol) {
            if (j.find('\'') == std::string::npos && variables.find(j) ==
                                                     variables.end()) { //                  if (headers.find(queryCol.at(j)) != headers.end()) { //

                result.append(((!addSpacer) ? "" : ", "));
//                    result.append(queryCol.at(j)); // This gets rid of the need to rename, but whatever :(
                int place = headers[j];
                std::string asd = table->getheaders().at(place - 1);
                result.append(asd); // Variable name
                result.append("=");
                result.append(row.at(place - 1));
                std::string re = row.at(place - 1);
                addSpacer = true;
                variables[j] = j;
            }
        }
        if (addSpacer)
            resultQue.push_back(result);
    }

    std::sort(resultQue.begin(), resultQue.end());

    for (auto &r: resultQue) {
        std::cout << "  " << r << std::endl;
    }
}

std::ostream &operator<<(std::ostream &os, Interpreter &interpreter) {
    return os;
}

void Interpreter::addRelation(Relation *relation) {
    this->relations.push_back(relation);
}

void Interpreter::clean() {
    for (auto &r : relations)
        delete r;
}
