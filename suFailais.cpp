#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <sstream>
#include <algorithm>

struct Studentas {
    std::string vardas;
    std::string pavarde;
    std::vector<int> Nd;
    int egz;
};

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

double skaiciuotiGalutiniBala(const Studentas& studentas, bool naudotiVidurki) {
    double NdBalas = skaiciuotiVidurki(studentas.Nd);
    double galutinisBalas = (0.4 * NdBalas + 0.6 * studentas.egz);
    if (naudotiVidurki) {
        return galutinisBalas;
    } else {
        double mediana = skaiciuotiMediana(studentas.Nd);
        return (0.4 * mediana + 0.6 * studentas.egz);
    }
}

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
