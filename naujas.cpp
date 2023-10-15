#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <random>
#include <chrono>

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

double skaiciuotiGalutiniBala(const Studentas& studentas) {
    double NdBalas = skaiciuotiVidurki(studentas.Nd);
    double galutinisBalas = (0.4 * NdBalas + 0.6 * studentas.egz);
    return galutinisBalas;
}


std::string generateName(int index) {
    return "Vardas" + std::to_string(index);
}


std::string generateSurname(int index) {
    return "Pavarde" + std::to_string(index);
}

int main() {
    std::vector<Studentas> studentai;

    int numberOfStudents;
    std::cout << "iveskite studentu skaiciu: ";
    std::cin >> numberOfStudents;

    auto startCreation = std::chrono::high_resolution_clock::now();

    
    for (int i = 1; i <= numberOfStudents; ++i) {
        Studentas naujasStudentas;
        naujasStudentas.vardas = generateName(i);
        naujasStudentas.pavarde = generateSurname(i);
        naujasStudentas.egz = rand() % 10 + 1; 

        for (int j = 0; j < 5; ++j) {
            naujasStudentas.Nd.push_back(rand() % 10 + 1); 
        }

        studentai.push_back(naujasStudentas);
    }

    auto endCreation = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diffCreation = endCreation - startCreation;
    std::cout << "Failo su " << numberOfStudents << " studentu/-ais kurimas uztruko: " << diffCreation.count() << " s\n";
    
    
    
    auto startRead = std::chrono::high_resolution_clock::now();
    auto endRead = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diffRead = endRead - startRead;
    std::cout << "Failo su " << numberOfStudents << " studentu/-ais nuskaitymas uztruko: " << diffRead.count() << " s\n";

    
    std::vector<Studentas> vargsiukai;
    std::vector<Studentas> galvociai;

    auto startSort = std::chrono::high_resolution_clock::now();

    for (const Studentas& studentas : studentai) {
        double galutinisBalasVidurkis = skaiciuotiGalutiniBala(studentas);
        if (galutinisBalasVidurkis < 5.0) {
            vargsiukai.push_back(studentas);
        } else {
            galvociai.push_back(studentas);
        }
    }

    auto endSort = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diffSort = endSort - startSort;
    std::cout << "Failo rusiavimas su " << numberOfStudents << " studentais i dvi grupes uztruko: " << diffSort.count() << " s\n";

    
    std::ofstream rezultataiFile("rezultatai.txt");
    rezultataiFile << std::setw(15) << std::left << "Vardas" << std::setw(15) << std::left << "Pavarde" << std::setw(10) << std::right << "Galutinis balas (vid.)" << std::endl;
    rezultataiFile << "---------------------------------------------------------------------" << std::endl;

    for (const Studentas& studentas : studentai) {
        double galutinisBalasVidurkis = skaiciuotiGalutiniBala(studentas);
        rezultataiFile << std::setw(15) << std::left << studentas.vardas << std::setw(15) << std::left << studentas.pavarde << std::setw(5) << std::fixed << std::setprecision(2) << std::right << galutinisBalasVidurkis << std::endl;
    }
    rezultataiFile.close();

    
    std::ofstream vargsiukaiFile("vargsiukai.txt");
    vargsiukaiFile << std::setw(15) << std::left << "Vardas" << std::setw(15) << std::left << "Pavarde" << std::setw(15) << std::right << "Galutinis balas (vid.)" << std::endl;
    vargsiukaiFile << "---------------------------------------------------------------------" << std::endl;

    auto startOutputVargsiukai = std::chrono::high_resolution_clock::now();

    for (const Studentas& studentas : vargsiukai) {
        double galutinisBalasVidurkis = skaiciuotiGalutiniBala(studentas);
        vargsiukaiFile << std::setw(15) << std::left << studentas.vardas << " " << std::setw(15) << std::left << studentas.pavarde << " " << std::fixed << std::setprecision(2) << std::right << galutinisBalasVidurkis << std::endl;
    }

    vargsiukaiFile.close();

    auto endOutputVargsiukai = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diffOutputVargsiukai = endOutputVargsiukai - startOutputVargsiukai;
    std::cout << "Failo isvedimas su " << numberOfStudents << " studentais i vargsiukus uztruko: " << diffOutputVargsiukai.count() << " s\n";

    
    std::ofstream galvociaiFile("galvociai.txt");
    galvociaiFile << std::setw(15) << std::left << "Vardas" << std::setw(15) << std::left << "Pavarde" << std::setw(15) << std::right << "Galutinis balas (vid.)" << std::endl;
    galvociaiFile << "---------------------------------------------------------------------" << std::endl;

    auto startOutputGalvociai = std::chrono::high_resolution_clock::now();

    for (const Studentas& studentas : galvociai) {
        double galutinisBalasVidurkis = skaiciuotiGalutiniBala(studentas);
        galvociaiFile << std::setw(15) << std::left << studentas.vardas << " " << std::setw(15) << std::left << studentas.pavarde << " " << std::fixed << std::setprecision(2) << std::right << galutinisBalasVidurkis << std::endl;
    }

    galvociaiFile.close();

    auto endOutputGalvociai = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diffOutputGalvociai = endOutputGalvociai - startOutputGalvociai;
    std::cout << "Failo isvedimas su " << numberOfStudents << " studentais i galvocius uztruko: " << diffOutputGalvociai.count() << " s\n";

    return 0;
}
