#include "vidurkis.h"

double skaiciuotiVidurki(const std::vector<int>& pazymiai) {
    if (pazymiai.empty()) {
        return 0.0;
    }
    double suma = 0.0;
    for (int pazymys : pazymiai) {
        suma += pazymys;
    }
    return suma / pazymiai.size();
}


