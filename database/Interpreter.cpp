//
// Created by bbrenk on 11/2/18.
//

#include "Interpreter.h"

Interpreter::~Interpreter() = default;

Interpreter *Interpreter::generateRelations(Schemes &schemes, Facts &facts) {
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

    return interp;
}

void Interpreter::proccessQueries(Interpreter *interpreter, Queries queries) {
    for (auto &q : queries.getQueries()) {
        for (auto &t : interpreter->relations) {
            if (t->getName() == q->getName()) {
                // Conduct query on this table
                std::list<std::pair<std::string, std::string>> list;
                for (unsigned int i = 0; i < q->getParams().size(); i++) {
                    std::vector<std::string> headers = t->getheaders();
                    list.emplace_back(headers.at(i), q->getParams().at(i));
                }
                std::cout << *q << "? ";
                auto result = t->select(list);
                std::cout << ((result->isEmpty()) ? "No" : "Yes(" + std::to_string(result->getRowCount()) + ")")
                          << std::endl;
                interpreter->printResults(q, result);
            }
        }
    }
}

void Interpreter::printResults(Query *query, Relation *table) {
    if (!table->isEmpty()) {
        std::unordered_map<std::string, int> headers = table->getHeadersMap();
        std::vector<std::vector<std::string>> rows = table->getRows();
        std::vector<std::string> queryCol = query->getParams();
        for (auto &row : rows) {
            bool addSpacer = false;
            std::string result;
            for (unsigned int j = 0; j < queryCol.size(); j++) {
                if (headers.find(queryCol.at(j)) != headers.end()) {
                    result.append(((j == 0) ? "" : ","));
                    result.append(queryCol.at(j));
                    result.append("=");
                    result.append(row.at(j));
                    addSpacer = true;
                }
            }
            if (addSpacer)
                std::cout << "  " << result << std::endl;
        }
    }
}

std::ostream &operator<<(std::ostream &os, Interpreter &interpreter) {
    return os;
}

void Interpreter::addRelation(Relation *relation) {
    this->relations.push_back(relation);
}
