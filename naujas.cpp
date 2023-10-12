#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
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


double skaiciuotiGalutiniBala(const Studentas& studentas, bool naudotiVidurki) {
    double NdBalas = skaiciuotiVidurki(studentas.Nd);
    double galutinisBalas = (0.4 * NdBalas + 0.6 * studentas.egz);
    return galutinisBalas;
}

int main() {
    std::vector<Studentas> studentai;
    char baloSkaiciavimoBudas;

    auto startReadFileTime = std::chrono::high_resolution_clock::now(); 

    std::ifstream inFile("kursiokai.txt");
    if (!inFile) {
        std::cerr << "Nepavyko atidaryti failo" << std::endl;
        return 1;
    }

    auto endReadFileTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> readFileTime = endReadFileTime - startReadFileTime;

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

    int studentCount = studentai.size(); 
    std::cout << "Studentų skaičius: " << studentCount << std::endl;

    std::cout << "Failo kursiokai.txt nuskaitymas uztruko: " << readFileTime.count() << " sekundes" << std::endl;

    std::ofstream rezultataiFile("rezultatai.txt");
    std::ofstream vargsiukaiFile("vargsiukai.txt");
    std::ofstream galvociaiFile("galvociai.txt");

    rezultataiFile << std::setw(15) << std::left << "Vardas" << std::setw(15) << std::left << "Pavardė" << std::setw(15) << std::right << "Galutinis (Vid.)"  << std::endl;
    rezultataiFile << "---------------------------------------------------------------------" << std::endl;

    vargsiukaiFile << std::setw(15) << std::left << "Vardas" << std::setw(15) << std::left << "Pavardė" << std::setw(15) << std::right << "Galutinis (Vid.)" << std::endl;
    vargsiukaiFile << "---------------------------------------------------------------------" << std::endl;

    galvociaiFile << std::setw(15) << std::left << "Vardas" << std::setw(15) << std::left << "Pavardė" << std::setw(15) << std::right << "Galutinis (Vid.)" << std::endl;
    galvociaiFile << "---------------------------------------------------------------------" << std::endl;


   for (const Studentas& studentas : studentai) {
        double galutinisBalasVidurkis = skaiciuotiGalutiniBala(studentas, true);

        rezultataiFile << std::setw(15) << std::left << studentas.vardas << std::setw(15) << std::left << studentas.pavarde << std::setw(5) << std::fixed << std::setprecision(2) << std::right << galutinisBalasVidurkis  << std::endl;

        if (galutinisBalasVidurkis < 5.0) {
            vargsiukaiFile << std::setw(15) << std::left << studentas.vardas << std::setw(15) << std::left << studentas.pavarde << std::setw(5) << std::fixed << std::setprecision(2) << std::right << galutinisBalasVidurkis << std::endl;
        } else {
            galvociaiFile << std::setw(15) << std::left << studentas.vardas << std::setw(15) << std::left << studentas.pavarde << std::setw(5) << std::fixed << std::setprecision(2) << std::right << galutinisBalasVidurkis << std::endl;
        }
    }

    rezultataiFile.close();
    vargsiukaiFile.close();
    galvociaiFile.close();

    return 0;

    
}

