#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>

struct Studentas {
    std::string vardas;
    std::string pavarde;
    std::vector<std::string> namuDarbai;
    int egzaminas;
};

double skaiciuotiVidurki(const std::vector<std::string>& pazymiai) {
    if (pazymiai.empty()) {
        return 0.0;
    }
    double suma = 0.0;
    for (const std::string& pazymys : pazymiai) {
        suma += std::stod(pazymys); // Konvertuojame į double
    }
    return suma / pazymiai.size();
}

double skaiciuotiMediana(const std::vector<std::string>& pazymiai) {
    if (pazymiai.empty()) {
        return 0.0;
    }
    std::vector<double> kopija;
    for (const std::string& pazymys : pazymiai) {
        kopija.push_back(std::stod(pazymys)); // Konvertuojame į double
    }
    std::sort(kopija.begin(), kopija.end());
    int dydis = kopija.size();
    if (dydis % 2 == 0) {
        double vidurinis1 = kopija[dydis / 2 - 1];
        double vidurinis2 = kopija[dydis / 2];
        return (vidurinis1 + vidurinis2) / 2.0;
    } else {
        return kopija[dydis / 2];
    }
}

double skaiciuotiGalutiniBala(const Studentas& studentas, bool naudotiVidurki) {
    double namuDarbuBalas = skaiciuotiVidurki(studentas.namuDarbai);
    double galutinisBalas = (0.4 * namuDarbuBalas + 0.6 * studentas.egzaminas);
    if (naudotiVidurki) {
        return galutinisBalas;
    } else {
        double mediana = skaiciuotiMediana(studentas.namuDarbai);
        return (0.4 * mediana + 0.6 * studentas.egzaminas);
    }
}

int main() {
    std::vector<Studentas> studentai;
    char pasirinkimas;

    do {
        Studentas naujasStudentas;
        std::cout << "Įveskite studento vardą: ";
        std::cin >> naujasStudentas.vardas;
        std::cout << "Įveskite studento pavardę: ";
        std::cin >> naujasStudentas.pavarde;

        std::string pazymys;
        std::cout << "Įveskite namų darbų rezultatus (baigti su punktu): ";
        while (std::cin >> pazymys) {
            if (pazymys == ".") {
                break; // Nutraukiame įvedimą, jei įvesta taškas
            }
            naujasStudentas.namuDarbai.push_back(pazymys);
        }

        std::cout << "Įveskite egzamino rezultatą: ";
        std::cin >> naujasStudentas.egzaminas;

        studentai.push_back(naujasStudentas);

        std::cout << "Ar norite įvesti dar vieno studento duomenis? (T/N): ";
        std::cin >> pasirinkimas;

    } while (pasirinkimas == 'T' || pasirinkimas == 't');

    std::cout << std::endl;
    std::cout << std::setw(15) << std::left << "Vardas" << std::setw(15) << std::left << "Pavardė" << std::setw(15) << std::right << "Galutinis (Vid.)" << std::setw(15) << std::right << "Galutinis (Med.)" << std::endl;
    std::cout << "-----------------------------------------------------------" << std::endl;

    for (const Studentas& studentas : studentai) {
        double galutinisVidurkiu = skaiciuotiGalutiniBala(studentas, true);
        double galutinisMediana = skaiciuotiGalutiniBala(studentas, false);

        std::cout << std::setw(15) << std::left << studentas.vardas << std::setw(15) << std::left << studentas.pavarde << std::setw(15) << std::fixed << std::setprecision(2) << std::right << galutinisVidurkiu << std::setw(15) << std::fixed << std::setprecision(2) << std::right << galutinisMediana << std::endl;
    }

    return 0;
}
