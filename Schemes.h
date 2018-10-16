//
// Created by bbrenk on 10/13/18.
//

#ifndef LAB2_SCHEMES_H
#define LAB2_SCHEMES_H


#include "Scheme.h"

class Schemes {
private:
    std::vector<Scheme *> schemes;
public:
    Schemes(std::vector<LexicalAnalyzer::token_struct> &list, unsigned int &index);

    friend std::ostream &operator<<(std::ostream &os, const Schemes &scheme) {
        os << "Schemes(" << scheme.schemes.size() << ")" << std::endl;
        for (auto &a: scheme.schemes) {
            os << "\t" << *a << std::endl;
        }
        return os;
    }

    void clean();
};


#endif //LAB2_SCHEMES_H
