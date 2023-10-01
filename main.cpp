#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <sstream>
#include "studentas.h"
#include "vidurkis.h"
#include "mediana.h"
#include "funkcijos.h"

int main() {
    std::vector<Studentas> studentai;
    char baloSkaiciavimoBudas;

    std::ifstream inFile("kursiokai.txt");
    if (!inFile) {
        std::cerr << "Nepavyko atidaryti failo" << std::endl;
        return 1;
    }

    std::string eilute;
    while (std::getline(inFile, eilute)) {
        std::istringstream iss(eilute);
        Studentas naujasStudentas;
        iss >> naujasStudentas.vardas >> naujasStudentas.pavarde;

        int pazymys;
        while (iss >> pazymys) {
            naujasStudentas.Nd.push_back(pazymys);
        }

        if (naujasStudentas.Nd.empty()) {
            continue;
        }

        naujasStudentas.egz = naujasStudentas.Nd.back();
        naujasStudentas.Nd.pop_back();

        studentai.push_back(naujasStudentas);
    }

    inFile.close();

    std::ofstream outFile("rezultatai.txt");

    outFile << std::setw(15) << std::left << "Vardas" << std::setw(15) << std::left << "Pavardė" << std::setw(15) << std::right << "Galutinis (Vid.)" << std::setw(15) << std::right << "Galutinis (Med.)" << std::endl;
    outFile << "---------------------------------------------------------------------" << std::endl;

    for (const Studentas& studentas : studentai) {
        double galutinisBalasVidurkis = skaiciuotiGalutiniBala(studentas, true);
        double galutinisBalasMediana = skaiciuotiGalutiniBala(studentas, false);

        outFile << std::setw(15) << std::left << studentas.vardas << std::setw(15) << std::left << studentas.pavarde << std::setw(15) << std::fixed << std::setprecision(2) << std::right << galutinisBalasVidurkis << std::setw(15) << std::fixed << std::setprecision(2) << std::right << galutinisBalasMediana << std::endl;
    }

    outFile.close();

    std::cout << "Rezultatai išsaugoti failo rezultatai.txt." << std::endl;

    return 0;
}


