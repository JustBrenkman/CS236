//
// Created by bbrenk on 10/15/18.
//

#include "Domain.h"

Domain::Domain() = default;

void Domain::addStringToDomain(std::string string) {
    for (auto &p : domain) {
        if (string == p)
            return;
    }
    domain.push_back(string);
}

std::string Domain::toString() {
    std::string domainS;

    domainS.append("Domain(");
    domainS.append(std::to_string(domain.size()));
    domainS.append(")\n");

    for (auto &d : domain) {
        domainS.append("  ");
        domainS.append(d);
        domainS.append("\n");
    }

    return domainS;
}
