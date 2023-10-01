#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

struct Studentas {
    std::string vardas;
    std::string pavarde;
    std::vector<int> Nd;
    int egz;
};

// Funkcija generuojan namu darbo balus nuo 1 iki 10
int generuotiNdBala() {
    return rand() % 10 + 1;
}

// Funkcija generuoja egzamino bala nuo 1 iki 10
int generuotiEgzBala() {
    return rand() % 10 + 1;
}

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
    char pasirinkimas;

    srand(time(nullptr));

    do {
        Studentas naujasStudentas;
        std::cout << "Įveskite studento vardą: ";
        std::cin >> naujasStudentas.vardas;
        std::cout << "Įveskite studento pavardę: ";
        std::cin >> naujasStudentas.pavarde;

        char generuotiPazymius;
        std::cout << "Ar norite, kad namų darbų ir egzamino pažymiai būtų generuojami? (T/N): ";
        std::cin >> generuotiPazymius;

        if (generuotiPazymius == 'T' || generuotiPazymius == 't') {
            int NdKiekis = rand() % 10 + 1;
            for (int i = 0; i < NdKiekis; ++i) {
                naujasStudentas.Nd.push_back(generuotiNdBala());
            }
            naujasStudentas.egz = generuotiEgzBala();
        } else {
            int pazymys;
            std::cout << "Įveskite namų darbų pažymius (baigus parašyk -1): ";
            while (std::cin >> pazymys) {
                if (pazymys == -1) {
                    break;
                }
                naujasStudentas.Nd.push_back(pazymys);
            }
            std::cout << "Įveskite egzamino pažymį: ";
            std::cin >> naujasStudentas.egz;
        }

        studentai.push_back(naujasStudentas);

        std::cout << "Ar norite įvesti dar vieno studento duomenis? (T/N): ";
        std::cin >> pasirinkimas;

    } while (pasirinkimas == 'T' || pasirinkimas == 't');

    char baloSkaiciavimoBudas;
    std::cout << "Kaip norite skaičiuoti galutinį balą pagal vidurkį (V) ar pagal medianą (M)? ";
    std::cin >> baloSkaiciavimoBudas;

    std::cout << std::endl;
    std::cout << std::setw(20) << std::left << "Vardas" << std::setw(20) << std::left << "Pavardė" << std::setw(20) << std::right;

    if (baloSkaiciavimoBudas == 'M' || baloSkaiciavimoBudas == 'm') {
        std::cout << "Galutinis (Med.)" << std::endl;
    } else {
        std::cout << "Galutinis (Vid.)" << std::endl;
    }
    
    std::cout << "---------------------------------------------------------------" << std::endl;

    for (const Studentas& studentas : studentai) {
        double galutinisBalas = (baloSkaiciavimoBudas == 'V' || baloSkaiciavimoBudas == 'v') ?
            skaiciuotiGalutiniBala(studentas, true) :
            skaiciuotiGalutiniBala(studentas, false);

        std::cout << std::setw(20) << std::left << studentas.vardas << std::setw(20) << std::left << studentas.pavarde << std::setw(7) << std::fixed << std::setprecision(2) << std::right << galutinisBalas << std::endl;
    }

    return 0;
}
