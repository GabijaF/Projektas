#include "mediana.h"
#include <algorithm>

double skaiciuotiMediana(const std::vector<int>& pazymiai) {
    if (pazymiai.empty()) {
        return 0.0;
    }
    std::vector<int> kopija = pazymiai;
    std::sort(kopija.begin(), kopija.end());
    int dydis = kopija.size();
    if (dydis % 2 == 0) {
        int vidurinis1 = kopija[dydis / 2 - 1];
        int vidurinis2 = kopija[dydis / 2];
        return (vidurinis1 + vidurinis2) / 2.0;
    } else {
        return kopija[dydis / 2];
    }
}


